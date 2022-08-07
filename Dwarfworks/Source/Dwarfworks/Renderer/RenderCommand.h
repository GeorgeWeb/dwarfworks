#ifndef GRAPHICS_RENDER_COMMAND_H
#define GRAPHICS_RENDER_COMMAND_H

#include "RendererAPI.h"

namespace Dwarfworks
{
// Important: Make sure that Render Commands DO NOT do multiple things!
class ENGINE_API RenderCommand final
{
  public:
    // Temp.
    ENGINE_API static void Initialize() { s_RendererAPI->Initialize(); }

    /**
     * @brief Set the Viewport object
     *
     * @param minX
     * @param minY
     * @param minZ
     * @param maxX
     * @param maxY
     * @param maxZ
     */
    ENGINE_API static void SetViewport(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
    {
        s_RendererAPI->SetViewport(minX, minY, 0, maxX, maxY, 0);
    }

    ENGINE_API static void SetViewport(float minX, float minY, float maxX, float maxY)
    {
        s_RendererAPI->SetViewport(minX, minY, 0, maxX, maxY, 0);
    }

    /**
     * @brief Set the Scissor object
     *
     * @param x
     * @param y
     * @param width
     * @param height
     */
    ENGINE_API static void SetScissor(int x, int y, uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetScissor(x, y, width, height);
    }

    ENGINE_API static void SetScissor(uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetScissor(0, 0, width, height);
    }

    /**
     * @brief Set the Blending object
     *
     * @param enable
     */
    ENGINE_API static void SetBlending(bool enable = true) { s_RendererAPI->SetBlending(enable); }

    /**
     * @brief Set the Depth Test object
     *
     * @param enable
     */
    ENGINE_API static void SetDepthTest(bool enable = true) { s_RendererAPI->SetDepthTest(enable); }

    /**
     * @brief Set the Scissor Test object
     *
     * @param enable
     */
    ENGINE_API static void SetScissorTest(bool enable = true) { s_RendererAPI->SetScissorTest(enable); }

    /**
     * @brief Set the Clear Color object
     *
     * @param color
     */
    ENGINE_API static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }

    /**
     * @brief
     *
     * @param mask
     * @return ENGINE_API
     */
    ENGINE_API static void Clear(int32 mask) { s_RendererAPI->Clear(mask); }

    /**
     * @brief
     *
     * @param baseVertexIndex
     * @param numPrimitives
     */
    ENGINE_API static void DrawPrimitive(uint32_t baseVertexIndex, uint32_t numPrimitives)
    {
        s_RendererAPI->DrawPrimitive(baseVertexIndex, numPrimitives);
    }

    /**
     * @brief
     *
     * @param indexBuffer
     * @param numVertices
     * @param baseVertexIndex
     * @param startIndex
     * @param numPrimitives
     */
    ENGINE_API static void DrawIndexedPrimitive(IndexBuffer* indexBuffer, uint32_t numVertices,
                                                       int32_t baseVertexIndex = 0, uint32_t startIndex = 0,
                                                       uint32_t numPrimitives = 1)
    {
        s_RendererAPI->DrawIndexedPrimitive(indexBuffer, numVertices, baseVertexIndex, startIndex, numPrimitives);
    }

  private:
    static Scope<RendererAPI> s_RendererAPI;
};

} // namespace Dwarfworks

#endif // GRAPHICS_RENDER_COMMAND_H
