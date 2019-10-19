#include "dwpch.h"

#include "OpenGLContext.h"

#include "Dwarfworks/Core/Log/Log.h"

// GLFW
#include <GLFW/glfw3.h>
// Glad
#include <glad/glad.h>
// OpenGL
#include <GL/GL.h>

namespace Dwarfworks {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle) {
  DW_CORE_ASSERT(windowHandle, "Window handle is null");
}

void OpenGLContext::Initialize() {
  glfwMakeContextCurrent(m_WindowHandle);
  auto status = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
  DW_CORE_ASSERT(status, "Failed to initialize Glad!");

  DW_CORE_INFO("OpenGL Info:");
  DW_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
  DW_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  DW_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

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
