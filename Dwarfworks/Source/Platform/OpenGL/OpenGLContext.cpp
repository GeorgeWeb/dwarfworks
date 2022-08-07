// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLContext.h"
#include "OpenGLLoader.h"

#include "Dwarfworks/Core/Log/Log.h"
#include "Dwarfworks/Renderer/RendererAPI.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace Dwarfworks;

OpenGLContext::OpenGLContext(GLFWwindow* handle)
    : m_OpenGLLoader {CreateRef<GLADOpenGLLoader>()}, m_WindowHandle {handle}
{
    DW_CORE_ASSERT(handle, "Window handle is invalid (null)");
}

void OpenGLContext::Initialize() const
{
    MakeContextCurrent();

    const bool loadedOpenGL = m_OpenGLLoader->LoadOpenGLFunctions();

    DW_CORE_ASSERT(loadedOpenGL, "Failed to initialize Glad!");

    auto OpenGLVendor   = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    auto OpenGLRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    auto OpenGLVersion  = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    DW_CORE_INFO("OpenGL Info:");
    DW_CORE_INFO("  Vendor: {0}", OpenGLVendor);
    DW_CORE_INFO("  Renderer: {0}", OpenGLRenderer);
    DW_CORE_INFO("  Version: {0}", OpenGLVersion);

    int DeviceAPIVersionMajor, DeviceAPIVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &DeviceAPIVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &DeviceAPIVersionMinor);

    DW_CORE_ASSERT(DeviceAPIVersionMajor > MinimumSupportedOpenGLVersionMajor ||
                       (DeviceAPIVersionMajor == MinimumSupportedOpenGLVersionMajor &&
                        DeviceAPIVersionMinor >= MinimumSupportedOpenGLVersionMinor),
                   "Dwarfworks requires at least OpenGL version 4.1");
}

void OpenGLContext::FlipSwapChainBuffers() const
{
    glfwSwapBuffers(m_WindowHandle);
}

void OpenGLContext::MakeContextCurrent() const
{
    glfwMakeContextCurrent(m_WindowHandle);
}
