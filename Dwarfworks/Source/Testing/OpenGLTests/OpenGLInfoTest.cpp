// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLInfoTest.h"

// glad
#include <glad/glad.h>
// imgui
#include "imgui.h"

namespace Testing {

void OpenGLInfoTest::OnDebugUIRender() {
  using namespace std::string_literals;

  auto OpenGLVendor = "Vendor: "s + (const char*)glGetString(GL_VENDOR);
  auto OpenGLRenderer = "Renderer: "s + (const char*)glGetString(GL_RENDERER);
  auto OpenGLVersion = "Version: "s + (const char*)glGetString(GL_VERSION);
  
  ImGui::Begin("OpenGL Info");
  ImGui::Text(OpenGLVendor.c_str());
  ImGui::Text(OpenGLRenderer.c_str());
  ImGui::Text(OpenGLVersion.c_str());
  ImGui::End();
}

}  // namespace Testing
