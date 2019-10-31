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
                      const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform /*=identity*/) {
  // TODO: Submit to a queue, then eval the render command, bind, then draw
  shader->Bind();
  // submit the view-projection matrix
  shader->UploadUniformMat4("u_ViewProjection",
                            m_SceneData->ViewProjectionMatrix);
  // submit the model matrix
  shader->UploadUniformMat4("u_Transform", transform);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Dwarfworks
