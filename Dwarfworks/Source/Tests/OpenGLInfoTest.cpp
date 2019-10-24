#include "dwpch.h"

#include "glad/glad.h"

#include "OpenGLInfoTest.h"

namespace Tests {

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
