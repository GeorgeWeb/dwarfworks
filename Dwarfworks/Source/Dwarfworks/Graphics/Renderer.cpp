// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer.h"

namespace Dwarfworks {

void Renderer::Initialize() {
  RenderCommand::Initialize();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
  // Note:
  // Needs to be reworked based on framebuffers in the future!
  // If rendering multiple viewports, upon window resizing we
  // don't want to immediately set the viewport to this.
  RenderCommand::SetViewport(0, 0, width, height);
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
