#ifndef GRAPHICS_RENDERER_API_H_
#define GRAPHICS_RENDERER_API_H_
#include "Dwarfworks/Graphics/VertexArray.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

class DW_API RendererAPI {
 public:
  enum class API { None = 0, OpenGL = 1 };

 public:
  virtual void Initialize() const = 0;

  virtual void SetViewport(int x, int y, uint32_t width,
                           uint32_t height) const = 0;

  virtual void SetClearColor(const glm::vec4 &color) const = 0;
  // TODO: Take in flags to what we actually wanna clear
  virtual void Clear() const = 0;

  virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) const = 0;

  inline static API GetAPI() { return s_API; };
  inline static void SetAPI(RendererAPI::API api) { s_API = api; };

 private:
  inline static API s_API = RendererAPI::API::OpenGL;
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDERER_API_H_
