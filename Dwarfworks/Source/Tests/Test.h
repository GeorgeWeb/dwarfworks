#ifndef TEST_H_
#define TEST_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Events/Event.h"
#include "Dwarfworks/Core/Layers/Layer.h"

#include "imgui.h"

namespace Tests {

class Test : public Dwarfworks::Layer {
 public:
  Test() : Layer("TestLayer") {}
  virtual ~Test() = default;

  virtual void OnUpdate() override {}
  virtual void OnRender() override {}  // TODO: Integrate with Renderer
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

template <class T>
void Tests::TestMenu::RegisterTest(const std::string& name) {
  DW_CORE_INFO("Registering test: {0}", name);
  m_TestList.push_back({name, [] { return new T(); }});
}

// ------------------------------------------------------------------
// --- TESTS --------------------------------------------------------
// ------------------------------------------------------------------

class BasicTest final : public Test {
 public:
  BasicTest() = default;

  void OnDebugUIRender() override final;
};

class ClearColorTest final : public Test {
 public:
  ClearColorTest();

  void OnRender() override final;
  void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

}  // namespace Tests

#endif  // TEST_H_
