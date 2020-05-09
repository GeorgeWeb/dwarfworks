// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer.h"

namespace Dwarfworks {

void Renderer::Initialize() { RenderCommand::Initialize(); }

void Renderer::OnFramebufferResize(uint32_t width, uint32_t height) {
  int x = 0, y = 0;
  RenderCommand::SetViewport(x, y, width, height);
}

void Renderer::BeginScene(OrthographicCamera& camera) {
  m_Scene->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader>& shader,
                      const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform /*=identity*/) {
  // bind shader
  shader->Bind();

  // submit the view-projection matrix
  shader->SetMat4("u_ViewProjection", m_Scene->ViewProjectionMatrix);
  // submit the model matrix
  shader->SetMat4("u_Transform", transform);
  // submit the light direction vector
  if (m_Scene->hasLight) {
    shader->SetFloat3("u_LightDir", m_Scene->LightDirectionVector);
  }

  // draw mesh
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Dwarfworks
