#ifndef GRAPHICS_RENDERER_API_H
#define GRAPHICS_RENDERER_API_H

#include "Dwarfworks/Renderer/Buffer.h"
#include "Dwarfworks/Math/Math.h"

// Temp. until we remove the non-generic concent of VertexArray
#include "Dwarfworks/Renderer/VertexArray.h"

namespace Dwarfworks
{
/**
 * @brief
 *
 */
enum ClearBufferMask : int32
{
    ColorBuffer   = BIT(0),
    DepthBuffer   = BIT(1),
    StencilBuffer = BIT(2)
};

/**
 * @brief Rendering Hardware Interface (RHI)
 *
 */
class ENGINE_API RendererAPI
{
  public:
    enum class API : uint8_t
    {
        OpenGL,
    };

    ENGINE_API inline static API GetAPI() { return s_API; };

  public:
    virtual ~RendererAPI() = default;

    // Temp.
    virtual void Initialize() const = 0;

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
    virtual void SetViewport(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) const = 0;
    void         SetViewport(float minX, float minY, float maxX, float maxY) const
    {
        SetViewport(minX, minY, 0, maxX, maxY, 0);
    }

    /**
     * @brief Set the Scissor object
     *
     * @param x
     * @param y
     * @param width
     * @param height
     */
    virtual void SetScissor(int x, int y, uint32_t width, uint32_t height) const = 0;
    void         SetScissor(uint32_t width, uint32_t height) const { SetScissor(0, 0, width, height); }

    /**
     * @brief Set the Blending object
     *
     * @param enable
     */
    virtual void SetBlending(bool enable = true) const    = 0;
    virtual void SetDepthTest(bool enable = true) const   = 0;
    virtual void SetScissorTest(bool enable = true) const = 0;

    /**
     * @brief Set the Clear Color object
     *
     * @param color
     */
    virtual void SetClearColor(const glm::vec4 &color) const = 0;

    /**
     * @brief
     *
     * @param mask
     */
    virtual void Clear(int32 mask) const = 0;

    /**
     * @brief
     *
     * @param baseVertexIndex
     * @param numPrimitives
     */
    virtual void DrawPrimitive(uint32_t baseVertexIndex, uint32_t numPrimitives) const = 0;

    /**
     * @brief
     *
     * @param indexBuffer
     * @param numVertices
     * @param baseVertexIndex
     * @param startIndex
     * @param numPrimitives
     */
    virtual void DrawIndexedPrimitive(IndexBuffer *indexBuffer, uint32_t numVertices, int32_t baseVertexIndex = 0,
                                      uint32_t startIndex = 0, uint32_t numPrimitives = 1) const = 0;

  private:
    ENGINE_API static API s_API;
};

} // namespace Dwarfworks

#endif // GRAPHICS_RENDERER_API_H
