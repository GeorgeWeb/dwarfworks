#include "dwpch.h"

#include "Test.h"

#include <glad/glad.h>

namespace Tests {

TestMenu::TestMenu(Test*& currentTestPointer)
    : m_CurrentTest(currentTestPointer) {}

void TestMenu::OnDebugUIRender() {
  for (auto& [name, instance] : m_TestList) {
    if (ImGui::Button(name.c_str())) {
      // set current test to an instance of the new test
      m_CurrentTest = instance();
    }
  }
}

// ------------------------------------------------------------------
// --- TESTS --------------------------------------------------------
// ------------------------------------------------------------------

// OpenGLClearColorTest

OpenGLClearColorTest::OpenGLClearColorTest()
    : m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f} {}

void OpenGLClearColorTest::OnRender() {
  // set clear color
  glClearColor(
      // red
      m_ClearColor.at(0),
      // green
      m_ClearColor.at(1),
      // blue
      m_ClearColor.at(2),
      // alpha
      m_ClearColor.at(3));
  // update color buffer
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLClearColorTest::OnDebugUIRender() {
  ImGui::ColorEdit4("Clear Color", m_ClearColor.data());
}

// OpenGLRenderTriangleColorTest

OpenGLRenderTriangleTest::OpenGLRenderTriangleTest() {
  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);

  glGenBuffers(1, &m_VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

  m_Vertices = {
      -0.5f, -0.5f, 0.0f,  // left
      0.5f,  -0.5f, 0.0f,  // right
      -0.0f, -0.5f, 0.0f,  // top
  };
}

void OpenGLRenderTriangleTest::OnUpdate() {}

void OpenGLRenderTriangleTest::OnRender() {}

void OpenGLRenderTriangleTest::OnDebugUIRender() {}

}  // namespace Tests
