// begin PCH
#include "dwpch.h"
// end PCH

#include "GraphicsContext.h"

#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Dwarfworks {

Scope<GraphicsContext> GraphicsContext::Create(void* window) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
	  DW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
	case RendererAPI::API::OpenGL:
	  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
  }

  DW_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace Dwarfworks
