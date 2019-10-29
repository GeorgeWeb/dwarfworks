#ifndef TEST_MENU_H_
#define TEST_MENU_H_

#include "Test.h"

namespace Tests {

class TestMenu final : public Test {
  using createTestFunc_t = std::function<Test*()>;

 public:
  explicit TestMenu(Test*& currentTestPointer);

  void OnDebugUIRender() override final;

  template <class T>
  void RegisterTest(const std::string& name);

 private:
  // reference to test pointer that allows mutation/change
  Test*& m_CurrentTest;

  // Test instance sort of structure in a contiguous collection
  std::vector<std::pair<std::string, createTestFunc_t>> m_TestList;
};

}  // namespace Tests

template <class T>
void Tests::TestMenu::RegisterTest(const std::string& name) {
  DW_CORE_INFO("Registering test: {0}", name);
  m_TestList.push_back({name, [] { return new T(); }});
}

#define INIT_TEST_MENU(menu, test) \
  { menu = CreateRef<Tests::TestMenu>(test); }

#define REGISTER_TEST(ttype, tname, menu) \
  { menu->RegisterTest<ttype>(tname); }

#endif  // TESTS_TEST_MENU_H_
