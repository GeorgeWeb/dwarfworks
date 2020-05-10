#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include "Dwarfworks/Graphics/Camera.h"
#include "Dwarfworks/Graphics/RenderCommand.h"
#include "Dwarfworks/Graphics/Shader.h"

namespace Dwarfworks {

class DW_API Renderer {
 public:
  static void Initialize();

  static void OnWindowResize(uint32_t width, uint32_t height);
  static void OnWindowResize(int x, int y, uint32_t width, uint32_t height);

  static void BeginScene(OrthographicCamera& camera);
  static void EndScene();

  static void Submit(const Ref<Shader>& shader,
                     const Ref<VertexArray>& vertexArray,
                     const glm::mat4& transform = glm::mat4(1.0f));

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

 private:
  // General scene storage (temporary)
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
    glm::vec3 LightDirectionVector;
    bool hasLight = false;
  };

  inline static Scope<SceneData> m_Scene = CreateScope<SceneData>();
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDERER_H_
