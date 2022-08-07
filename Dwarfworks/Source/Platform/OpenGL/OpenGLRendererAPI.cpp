// begin PCH
#include "dwpch.h"
// end PCH

#include "OpenGLRendererAPI.h"
#include "OpenGLVertexArray.h"

#ifdef DW_DEBUG
    #include "OpenGLError.h"
#endif

#include "glad/glad.h"

using namespace Dwarfworks;

void OpenGLRendererAPI::Initialize() const
{
#ifdef DW_DEBUG
    // OpenGL 4.3
    // glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // glDebugMessageCallback(OpenGL::MessageCallback, nullptr);
    // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    //
    // TODO: Use GLVerify(...) macro :'( (or OpenGL::Verify(...) tmp function)
    // OpenGL::Verify();
#endif

    SetBlending(true);
    SetDepthTest(false);
}

inline void OpenGLRendererAPI::SetBlending(bool enable) const
{
    if (enable)
    {
        glEnable(GL_BLEND);
        // TODO(georgi): Abstract in a SetBlendFunction interface
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }
}

inline void OpenGLRendererAPI::SetDepthTest(bool enable) const
{
    if (enable)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

inline void OpenGLRendererAPI::SetScissorTest(bool enable) const
{
    if (enable)
    {
        glEnable(GL_SCISSOR_TEST);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

inline void OpenGLRendererAPI::SetViewport(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) const
{
    (void) (minZ);
    (void) (maxZ);
    const auto x      = static_cast<int32_t>(minX);
    const auto y      = static_cast<int32_t>(minY);
    const auto width  = static_cast<int32_t>(maxX);
    const auto height = static_cast<int32_t>(maxY);
    glViewport(x, y, width, height);
}

inline void OpenGLRendererAPI::SetScissor(int32_t x, int32_t y, uint32_t width, uint32_t height) const
{
    glScissor(x, y, width, height);
}

inline void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const
{
    glClearColor(color.r, color.g, color.b, color.a);
}

inline void OpenGLRendererAPI::Clear(int32 mask) const
{
    static const auto ConvertMaskToBitfield = [mask]() {
        GLbitfield bitmask = {0};
        if (mask & ClearBufferMask::ColorBuffer)
        {
            bitmask |= GL_COLOR_BUFFER_BIT;
        }
        if (mask & ClearBufferMask::DepthBuffer)
        {
            bitmask |= GL_DEPTH_BUFFER_BIT;
        }
        if (mask & ClearBufferMask::StencilBuffer)
        {
            bitmask |= GL_STENCIL_BUFFER_BIT;
        }
        return bitmask;
    };

    const GLbitfield bitmask = ConvertMaskToBitfield();
    glClear(bitmask);
}

inline void OpenGLRendererAPI::DrawPrimitive(uint32_t baseVertexIndex, uint32_t numPrimitives) const
{
    // TODO(georgi): Implement non-indexed variant
}

inline void OpenGLRendererAPI::DrawIndexedPrimitive(IndexBuffer* indexBuffer, uint32_t numVertices,
                                                    int32_t baseVertexIndex, uint32_t startIndex,
                                                    uint32_t numPrimitives) const
{
    static constexpr auto mode = GL_TRIANGLES;
    static constexpr auto type = GL_UNSIGNED_INT;

    const int32_t  baseVertex = baseVertexIndex * numVertices;
    const uint32_t indexCount = indexBuffer->GetCount();
    uint32_t       indices    = startIndex;

    for (uint32_t primitiveIndex = 0; primitiveIndex < numPrimitives; ++primitiveIndex)
    {
        glDrawElementsBaseVertex(mode, indexCount, type, reinterpret_cast<const void*>(indices), baseVertex);
    }
}
