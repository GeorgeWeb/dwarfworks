// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer2D.h"

using namespace Dwarfworks;

void Renderer2D::Initialize()
{
    RenderCommand::Initialize();
}

void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
{
    OnWindowResize(0, 0, width, height);
}

void Renderer2D::OnWindowResize(int x, int y, uint32_t width, uint32_t height)
{
    RenderCommand::SetViewport(x, y, width, height);
    RenderCommand::SetScissor(x, y, width, height);
}

void Renderer2D::BeginScene(OrthographicCamera& camera)
{
    m_Scene->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer2D::EndScene()
{
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture)
{
}
