#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include "Dwarfworks/Core/Core.h"

namespace Dwarfworks {

enum class RendererAPI { None = 0, OpenGL = 1 };

class DW_API Renderer {
 public:
  inline static RendererAPI GetCurrentAPI() { return s_RendererAPI; }
  inline static void SetCurrentAPI(RendererAPI api) { s_RendererAPI = api; }

 private:
  inline static RendererAPI s_RendererAPI = RendererAPI::OpenGL;
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_RENDERER_H_
