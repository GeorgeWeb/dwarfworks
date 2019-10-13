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

// BasicTest

void BasicTest::OnDebugUIRender() {
  ImGui::Begin("Basic Test");
  ImGui::Text("Hello from Basic Test!");
  ImGui::End();
}

// ClearColorTest

ClearColorTest::ClearColorTest() : m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f} {}

void ClearColorTest::OnRender() {
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

void ClearColorTest::OnDebugUIRender() {
  ImGui::ColorEdit4("Clear Color", m_ClearColor.data());
}

}  // namespace Tests
