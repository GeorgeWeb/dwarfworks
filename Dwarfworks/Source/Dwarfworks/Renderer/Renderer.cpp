// begin PCH
#include "Dwarfworks/Renderer/Buffer.h"
#include "dwpch.h"
// end PCH

#include "Renderer.h"

using namespace Dwarfworks;

void Renderer::Initialize()
{
    RenderCommand::Initialize();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    OnWindowResize(0, 0, width, height);
}

void Renderer::OnWindowResize(int x, int y, uint32_t width, uint32_t height)
{
    RenderCommand::SetViewport(x, y, width, height);
    RenderCommand::SetScissor(x, y, width, height);
}

void Renderer::BeginScene(OrthographicCamera& camera)
{
    m_Scene->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
{
    // bind shader
    shader->Bind();

    // submit the view-projection matrix
    shader->SetMat4("u_ViewProjection", m_Scene->ViewProjectionMatrix);
    // submit the model matrix
    shader->SetMat4("u_Transform", transform);
    // submit the light direction vector
    if (m_Scene->hasLight)
    {
        shader->SetFloat3("u_LightDir", m_Scene->LightDirectionVector);
    }

    // draw mesh
    vertexArray->Bind();

    auto           indexBuffer = vertexArray->GetIndexBuffer();
    const uint32_t numVertices = vertexArray->GetVertexBuffers()[0]->GetLayout().GetElementCount();
    RenderCommand::DrawIndexedPrimitive(indexBuffer.get(), numVertices);
}
