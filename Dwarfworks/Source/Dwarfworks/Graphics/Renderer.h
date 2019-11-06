#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include "Dwarfworks/Graphics/Camera.h"
#include "Dwarfworks/Graphics/Material.h"
#include "Dwarfworks/Graphics/RenderCommand.h"
#include "Dwarfworks/Graphics/Shader.h"
// TEMPORARY
#include "Platform/OpenGL/OpenGLShader.h"

namespace Dwarfworks {

class DW_API Renderer {
 public:
  static void BeginScene(OrthographicCamera& camera);
  static void EndScene();

  static void Submit(const Ref<Shader>& shader,
                     const Ref<VertexArray>& vertexArray,
                     const glm::mat4& transform = glm::mat4(1.0f));

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

 private:
  // storage (TEMPORARY!)
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  inline static Scope<SceneData> m_SceneData = CreateScope<SceneData>();
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDERER_H_
