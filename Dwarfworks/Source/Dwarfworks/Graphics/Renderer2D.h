#ifndef GRAPHICS_RENDERER_2D_H_
#define GRAPHICS_RENDERER_2D_H_

#include "Dwarfworks/Graphics/Camera.h"
#include "Dwarfworks/Graphics/RenderCommand.h"
#include "Dwarfworks/Graphics/Shader.h"
#include "Dwarfworks/Graphics/Texture.h"

namespace Dwarfworks {

class DW_API Renderer2D {
 public:
  static void Initialize();

  static void BeginScene(OrthographicCamera& camera);
  static void EndScene();

  static void DrawQuad(const glm::vec3& position, const glm::vec3& size,
                       const glm::vec4& color);
  static void DrawQuad(const glm::vec3& position, const glm::vec3& size,
                       const Ref<Texture2D>& texture);

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
