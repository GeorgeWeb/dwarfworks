#ifndef TEST_H_
#define TEST_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Layers/Layer.h"

namespace Testing {

class Test : public Dwarfworks::Layer {
 public:
  Test() : Layer() {}
  // Test(const std::string& name) : Layer(name) {}

  virtual ~Test() = default;

  virtual void OnRender() override {}
  virtual void OnDebugUIRender() override {}
};

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

}  // namespace Testing

template <class T>
void Testing::TestMenu::RegisterTest(const std::string& name) {
  DW_CORE_INFO("Registering test: {0}", name);
  m_TestList.push_back({name, [] { return new T(); }});
}

#define INIT_TEST_MENU(menu, test) \
  { menu = CreateRef<Testing::TestMenu>(test); }

#define REGISTER_TEST(ttype, tname, menu) \
  { menu->RegisterTest<ttype>(tname); }

#endif  // TEST_H_
