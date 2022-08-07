#ifndef PLATFORM_OPENGL_OPENGL_RENDERER_API_H
#define PLATFORM_OPENGL_OPENGL_RENDERER_API_H

#include "Dwarfworks/Renderer/RendererAPI.h"

// struct VertexArray;

namespace Dwarfworks
{
class ENGINE_API OpenGLRendererAPI final : public RendererAPI
{
  public:
    ~OpenGLRendererAPI() override final = default;

    // Temp.
    void Initialize() const override final;

    void SetViewport(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) const override final;
    void SetScissor(int x, int y, uint32_t width, uint32_t height) const override final;

    void SetBlending(bool enable = true) const override final;
    void SetDepthTest(bool enable = true) const override final;
    void SetScissorTest(bool enable = true) const override final;

    void SetClearColor(const glm::vec4& color) const override final;
    void Clear(int32 mask) const override final;

    void DrawPrimitive(uint32_t baseVertexIndex, uint32_t numPrimitives) const override final;

    void DrawIndexedPrimitive(IndexBuffer* indexBuffer, uint32_t numVertices, int32_t baseVertexIndex = 0,
                              uint32_t startIndex = 0, uint32_t numPrimitives = 1) const override final;
};
} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_RENDERER_API_H
