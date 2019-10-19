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
  glClearColor(m_ClearColor.at(0),   // r
               m_ClearColor.at(1),   // g
               m_ClearColor.at(2),   // b
               m_ClearColor.at(3));  // a
  // update color buffer
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLClearColorTest::OnDebugUIRender() {
  ImGui::ColorEdit4("Clear Color", m_ClearColor.data());
}

// OpenGLRenderTriangleTest

OpenGLRenderTriangleTest::OpenGLRenderTriangleTest() {
  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);

  glGenBuffers(1, &m_VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

  float vertices[9] = {-0.5f, -0.5f, 0.0f,   // left
                       0.5f,  -0.5f, 0.0f,   // right
                       0.0f,  0.5f,  0.0f};  // top

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  glGenBuffers(1, &m_IndexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

  unsigned int indices[3] = {0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
}

void OpenGLRenderTriangleTest::OnRender() {
  glBindVertexArray(m_VertexArray);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

// OpenGLInfoTest

void OpenGLInfoTest::OnDebugUIRender() {
  using namespace std::string_literals;

  ImGui::Begin("OpenGL Info");
  const auto vendor = "Vendor: "s + (const char*)glGetString(GL_VENDOR);
  const auto renderer = "Renderer: "s + (const char*)glGetString(GL_RENDERER);
  const auto version = "Version: "s + (const char*)glGetString(GL_VERSION);
  ImGui::Text(vendor.c_str());
  ImGui::Text(renderer.c_str());
  ImGui::Text(version.c_str());
  ImGui::End();
}

}  // namespace Tests
