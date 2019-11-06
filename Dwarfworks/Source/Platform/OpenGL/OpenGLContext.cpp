// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Core/Log/Log.h"
#include "OpenGLContext.h"

// GLFW
#include <GLFW/glfw3.h>
// Glad
#include <glad/glad.h>

namespace Dwarfworks {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle) {
  DW_CORE_ASSERT(windowHandle, "Window handle is null");
}

void OpenGLContext::Initialize() {
  glfwMakeContextCurrent(m_WindowHandle);
  auto status = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
  DW_CORE_ASSERT(status, "Failed to initialize Glad!");

  auto OpenGLVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  auto OpenGLRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  auto OpenGLVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  
  DW_CORE_INFO("OpenGL Info:");
  DW_CORE_INFO("  Vendor: {0}", OpenGLVendor);
  DW_CORE_INFO("  Renderer: {0}", OpenGLRenderer);
  DW_CORE_INFO("  Version: {0}", OpenGLVersion);

#ifdef DW_ENABLE_ASSERTS
  int versionMajor;
  int versionMinor;
  glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
  glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

  DW_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
                 "Dwarfworks requires at least OpenGL version 4.5!");
#endif
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

}  // namespace Dwarfworks
