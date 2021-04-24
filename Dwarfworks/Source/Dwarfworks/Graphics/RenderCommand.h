#ifndef GRAPHICS_RENDER_COMMAND_H_
#define GRAPHICS_RENDER_COMMAND_H_

// TODO: This include should be removed and the API should be set dynamically
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dwarfworks
{
// Important: Make sure that Render Commands DO NOT do multiple things!
class ENGINE_API RenderCommand
{
  public:
    inline static void Initialize() { s_RendererAPI->Initialize(); }

    inline static void SetViewport(uint32_t width, uint32_t height) { SetViewport(0, 0, width, height); }

    inline static void SetViewport(int x, int y, uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetViewport(x, y, width, height);
    }

    inline static void SetScissor(uint32_t width, uint32_t height) { s_RendererAPI->SetScissor(0, 0, width, height); }

    inline static void SetScissor(int x, int y, uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetScissor(x, y, width, height);
    }

    inline static void SetBlending(bool enable = true) { s_RendererAPI->SetBlending(enable); }

    inline static void SetDepthTest(bool enable = true) { s_RendererAPI->SetDepthTest(enable); }

    inline static void SetScissorTest(bool enable = true) { s_RendererAPI->SetScissorTest(enable); }

    inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }

    inline static void Clear(uint32_t target = BufferTarget::Color) { s_RendererAPI->Clear(target); }

    // Draws indexed primitives
    inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

    // TODO:
    // inline static void DrawMasked(const Ref<VertexArray>& vertexArray);
    // inline static void DrawOutlined(const Ref<VertexArray>& vertexArray);

  private:
    // TODO: set dynamically (in the future)
    inline static Scope<RendererAPI> s_RendererAPI = CreateScope<OpenGLRendererAPI>();
};

} // namespace Dwarfworks

#endif // GRAPHICS_RENDER_COMMAND_H_
