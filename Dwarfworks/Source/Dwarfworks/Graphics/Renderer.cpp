// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer.h"

namespace Dwarfworks {

void Renderer::BeginScene(OrthographicCamera& camera) {
  m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader>& shader,
                      const Ref<VertexArray>& vertexArray) {
  // TODO: Submit to a queue, then eval the render command, bind, then draw
  shader->Bind();
  shader->UploadUniformMat4("u_ViewProjection",
                            m_SceneData->ViewProjectionMatrix);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Dwarfworks
