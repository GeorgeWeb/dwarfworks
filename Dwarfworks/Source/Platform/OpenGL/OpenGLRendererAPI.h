#ifndef PLATFORM_OPENGL_OPENGL_RENDERER_API_H_
#define PLATFORM_OPENGL_OPENGL_RENDERER_API_H_

#include "Dwarfworks/Graphics/RendererAPI.h"

namespace Dwarfworks
{
class ENGINE_API OpenGLRendererAPI : public RendererAPI
{
  public:
    virtual void Initialize() const override;

    virtual void SetViewport(int x, int y, uint32_t width, uint32_t height) const override;

    virtual void SetScissor(int x, int y, uint32_t width, uint32_t height) const override;

    virtual void SetBlending(bool enable = true) const override;
    virtual void SetDepthTest(bool enable = true) const override;
    virtual void SetScissorTest(bool enable = true) const override;

    virtual void SetClearColor(const glm::vec4& color) const override;
    virtual void Clear(uint32_t target = BufferTarget::Color) const override;

    virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const override;
};
} // namespace Dwarfworks

#endif // PLATFORM_OPENGL_OPENGL_RENDERER_API_H_
