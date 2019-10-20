#ifndef TEST_H_
#define TEST_H_

#include "Dwarfworks/Core/Core.h"
// #include "Dwarfworks/Core/Events/Event.h"
#include "Dwarfworks/Core/Layers/Layer.h"
#include "Dwarfworks/Graphics/Shader.h"

#include "imgui.h"

namespace Tests {

class Test : public Dwarfworks::Layer {
 public:
  Test() : Layer("TestLayer") {}
  virtual ~Test() = default;

  // virtual void OnEvent(Dwarfworks::Event& event) override {}
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

class OpenGLInfoTest final : public Test {
 public:
  OpenGLInfoTest() = default;

  void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

class OpenGLClearColorTest final : public Test {
 public:
  OpenGLClearColorTest();

  void OnRender() override final;
  void OnDebugUIRender() override final;

 private:
  std::array<float, 4> m_ClearColor;
};

class OpenGLRenderTriangleTest final : public Test {
 public:
  OpenGLRenderTriangleTest();

  void OnRender() override final;

 private:
  unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
  Dwarfworks::Scope<Dwarfworks::Shader> m_Shader;
};

}  // namespace Tests

#endif  // TEST_H_
