#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include "Dwarfworks/Graphics/RenderCommand.h"

namespace Dwarfworks {

class DW_API Renderer {
 public:
  static void BeginScene(/*scene params...*/);
  static void EndScene();

  // TODO: VertexArray -> Mesh -> Model -> (GameObject?)
  static void Submit(const Ref<VertexArray>& vertexArray);

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDERER_H_
