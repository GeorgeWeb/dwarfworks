// begin PCH
#include "dwpch.h"
// end PCH

#include "Renderer2D.h"

namespace Dwarfworks
{
void Renderer2D::Initialize()
{
    RenderCommand::Initialize();
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

} // namespace Dwarfworks
