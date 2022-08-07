#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "Dwarfworks/Renderer/Camera.h"
#include "Dwarfworks/Renderer/RenderCommand.h"
#include "Dwarfworks/Renderer/Shader.h"

namespace Dwarfworks
{
// template <class T>
// class ENGINE_API Renderer : CRTP<T>
class ENGINE_API Renderer
{
  public:
    static void Initialize();

    // TODO(georgi): These should be abstracted in a Viewport class!
    static void OnWindowResize(uint32_t width, uint32_t height);
    static void OnWindowResize(int x, int y, uint32_t width, uint32_t height);

    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));

    template <class TMesh>
    static void Submit(const Ref<Shader>& shader, const Ref<TMesh>& mesh)
    {
        // TODO(georgi): Implement when we remove the dependencny on VAO.
    }

    ENGINE_API static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

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

/*
class ENGINE_API ForwardRenderer : public Renderer<ForwardRenderer>
{
  public:
};
*/

} // namespace Dwarfworks

#endif // GRAPHICS_RENDERER_H
