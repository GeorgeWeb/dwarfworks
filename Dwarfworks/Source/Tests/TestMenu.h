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

// Template is in Header file as solution to linking problems
// Note: may bloat codee of our executable file
template <class T>
void Tests::TestMenu::RegisterTest(const std::string& name) {
  DW_CORE_INFO("Registering test: {0}", name);
  m_TestList.push_back({name, [] { return new T(); }});
}
#endif  // TESTS_TEST_MENU_H_
