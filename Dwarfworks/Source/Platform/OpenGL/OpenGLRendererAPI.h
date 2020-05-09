#ifndef PLATFORM_OPENGL_OPENGL_RENDERER_API_H_
#define PLATFORM_OPENGL_OPENGL_RENDERER_API_H_

#include "Dwarfworks/Graphics/RendererAPI.h"

namespace Dwarfworks {
class DW_API OpenGLRendererAPI : public RendererAPI {
 public:
  virtual void Initialize() const override;

  virtual void SetViewport(int x, int y, uint32_t width,
                           uint32_t height) const override;

  virtual void SetClearColor(const glm::vec4& color) const override;
  virtual void Clear() const override;

  virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const override;
};
}  // namespace Dwarfworks

#endif  // PLATFORM_OPENGL_OPENGL_RENDERER_API_H_
