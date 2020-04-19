#ifndef GRAPHICS_RENDER_COMMAND_H_
#define GRAPHICS_RENDER_COMMAND_H_

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dwarfworks {

// Important: Make sure that Render Commands DO NOT do multiple things!
class DW_API RenderCommand {
 public:
  inline static void SetClearColor(const glm::vec4& color) {
    s_RendererAPI->SetClearColor(color);
  }

  inline static void Clear() { s_RendererAPI->Clear(); }

  // Draws indexed primitives
  inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
    s_RendererAPI->DrawIndexed(vertexArray);
  }

  // TODO:
  // inline static void DrawMasked(const Ref<VertexArray>& vertexArray);
  // inline static void DrawOutlined(const Ref<VertexArray>& vertexArray);

 private:
  // TODO: set dynamically (in the future)
  inline static Scope<RendererAPI> s_RendererAPI =
      CreateScope<OpenGLRendererAPI>();
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDER_COMMAND_H_
