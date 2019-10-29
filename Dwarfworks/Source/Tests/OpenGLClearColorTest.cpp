// begin PCH
#include "dwpch.h"
// end PCH

#include <glad/glad.h>

#include "OpenGLClearColorTest.h"

namespace Tests {

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

}  // namespace Tests
