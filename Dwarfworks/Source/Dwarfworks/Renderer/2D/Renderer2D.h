#ifndef GRAPHICS_RENDERER_2D_H
#define GRAPHICS_RENDERER_2D_H

#include "Dwarfworks/Renderer/Camera.h"
#include "Dwarfworks/Renderer/RenderCommand.h"
#include "Dwarfworks/Renderer/Shader.h"
#include "Dwarfworks/Renderer/Texture.h"

namespace Dwarfworks
{
class ENGINE_API Renderer2D
{
  public:
    static void Initialize();

    static void OnWindowResize(uint32_t width, uint32_t height);
    static void OnWindowResize(int x, int y, uint32_t width, uint32_t height);

    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec3& size, const Ref<Texture2D>& texture);

    ENGINE_API inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

  private:
    // General scene storage (temporary)
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
        glm::vec3 LightDirectionVector;
        bool      hasLight = false;
    };

    inline static Scope<SceneData> m_Scene = CreateScope<SceneData>();
};

} // namespace Dwarfworks

#endif // GRAPHICS_RENDERER_H
