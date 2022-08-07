#pragma once

#include "Dwarfworks/Core/Core.h"
#include <string_view>

namespace Dwarfworks::OpenGL
{
#if 0 // OpenGL 4.3
// Callback for OpenGL API calls error debugging
static void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                            const GLchar* message, const void* userParam)
{
    using namespace std::literals::string_view_literals;
    std::string_view sourceStr = [source]() {
        switch (source)
        {
            case GL_DEBUG_SOURCE_API: return "API"sv;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM"sv;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER"sv;
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY"sv;
            case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION"sv;
            case GL_DEBUG_SOURCE_OTHER: return "OTHER"sv;
            default: return ""sv;
        }
    }();

    std::string_view typeStr = [type]() {
        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR: return "ERROR"sv;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR"sv;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR"sv;
            case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY"sv;
            case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE"sv;
            case GL_DEBUG_TYPE_MARKER: return "MARKER"sv;
            case GL_DEBUG_TYPE_OTHER: return "OTHER"sv;
            default: return ""sv;
        }
    }();

    std::string_view severityStr = [severity]() {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION"sv;
            case GL_DEBUG_SEVERITY_LOW: return "LOW"sv;
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM"sv;
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH"sv;
            default: return ""sv;
        }
    }();

    DW_CORE_ERROR("GL ERROR!\nSource: {}\n Type:{}\nSeverity: {}\nID: {}\nMessage: {}\n", sourceStr, typeStr,
                  severityStr, id, message);
}
#endif

/**
 * @brief
 *
 */
// template <>
inline void Verify()
{
}

} // namespace Dwarfworks::OpenGL
