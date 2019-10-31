#ifndef GRAPHICS_RENDER_COMMAND_H_
#define GRAPHICS_RENDER_COMMAND_H_

#include "Platform/OpenGL/OpenGLRendererAPI.h"
// #include "RendererAPI.h"

namespace Dwarfworks {

class DW_API RenderCommand {
 public:
  inline static void SetClearColor(const glm::vec4& color) {
    s_RendererAPI->SetClearColor(color);
  }

  inline static void Clear() { s_RendererAPI->Clear(); }

  inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
    s_RendererAPI->DrawIndexed(vertexArray);
  }

 private:
  // TODO: set dynamically (in the future)
  inline static Scope<RendererAPI> s_RendererAPI =
      CreateScope<OpenGLRendererAPI>();
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDER_COMMAND_H_
