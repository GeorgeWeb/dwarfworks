// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer.h"

namespace Dwarfworks {

void Renderer::BeginScene(/*scene params...*/) {}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<VertexArray>& vertexArray) {
  // TODO: Submit to a queue, then eval the render command, bind, then draw
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Dwarfworks
