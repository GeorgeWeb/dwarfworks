// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer.h"

namespace Dwarfworks {

void Renderer::BeginScene(OrthographicCamera& camera) {
  m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<MaterialInstance>& materialInstance,
                      const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform) {
  // TODO: Submit to a queue, then eval the render command, bind, then draw
  materialInstance->GetMaterial()->GetShader()->Bind();
  // submit the view-projection matrix
  materialInstance->GetMaterial()->GetShader()->UploadUniformMat4(
      "u_ViewProjection", m_SceneData->ViewProjectionMatrix);
  // submit the model matrix
  materialInstance->GetMaterial()->GetShader()->UploadUniformMat4("u_Transform",
                                                                  transform);

  // bind material uniforms
  materialInstance->Bind();

  // draw mesh
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Dwarfworks
