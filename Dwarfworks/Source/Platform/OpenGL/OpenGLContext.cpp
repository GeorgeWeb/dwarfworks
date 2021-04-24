// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Core/Log/Log.h"
#include "Dwarfworks/Graphics/RendererAPI.h"

#include "OpenGLContext.h"

// GLFW
#include <GLFW/glfw3.h>
// Glad
#include <glad/glad.h>

// Callback for OpenGL API calls error debugging
static void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                            const GLchar* message, const void* userParam)
{
    std::string_view sourceStr = [source]() {
        switch (source)
        {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER: return "OTHER";
            default: return "";
        }
    }();

    std::string_view typeStr = [type]() {
        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR: return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER: return "MARKER";
            case GL_DEBUG_TYPE_OTHER: return "OTHER";
            default: return "";
        }
    }();

    std::string_view severityStr = [severity]() {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW: return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            default: return "";
        }
    }();

    DW_CORE_ERROR("GL ERROR!\nSource: {}\n Type:{}\nSeverity: {}\nID: {}\nMessage: {}\n", sourceStr, typeStr,
                  severityStr, id, message);
}

using namespace Dwarfworks;

OpenGLContext::OpenGLContext(GLFWwindow* handle) : m_WindowHandle(handle)
{
    DW_CORE_ASSERT(handle, "Window handle is null");
}

void OpenGLContext::Initialize()
{
    glfwMakeContextCurrent(m_WindowHandle);
    auto status = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
    DW_CORE_ASSERT(status, "Failed to initialize Glad!");

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
                   "Dwarfworks requires at least OpenGL version 4.3");

    GAPIVersionMajor = DeviceAPIVersionMajor;
    GAPIVersionMinor = DeviceAPIVersionMinor;

#ifdef DW_DEBUG
    if (GLAD_GL_VERSION_4_3)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, nullptr);
    }
#endif
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
