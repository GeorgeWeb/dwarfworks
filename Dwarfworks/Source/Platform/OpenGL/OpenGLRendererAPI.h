#ifndef PLATFORM_OPENGL_OPENGL_RENDERER_API_H_
#define PLATFORM_OPENGL_OPENGL_RENDERER_API_H_

#include "Dwarfworks/Graphics/RendererAPI.h"

namespace Dwarfworks {
class DW_API OpenGLRendererAPI : public RendererAPI {
 public:
  virtual void SetClearColor(const glm::vec4& color) override;
  virtual void Clear() override;

  virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
};
}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_RENDERER_API_H_
