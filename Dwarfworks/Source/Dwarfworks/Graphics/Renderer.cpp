// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer.h"

// TEMPORARY
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dwarfworks {

void Renderer::Initialize() {
  RenderCommand::Initialize();
}

void Renderer::BeginScene(OrthographicCamera& camera) {
  m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader>& shader,
                      const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform /*=identity*/) {
  // bind shader
  shader->Bind();

  // submit the view-projection matrix
  shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
  // submit the model matrix
  shader->SetMat4("u_Transform", transform);
  // submit the light direction vector
  if (m_SceneData->hasLight) {
	shader->SetFloat3("u_LightDir", m_SceneData->LightDirectionVector);
  }

  // draw mesh
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

}  // namespace Dwarfworks
