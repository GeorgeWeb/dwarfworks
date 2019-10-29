// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Graphics/Renderer.h"
#include "Dwarfworks/Platform/OpenGL/OpenGLVertexArray.h"
#include "VertexArray.h"

namespace Dwarfworks {

VertexArray* VertexArray::Create() {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      DW_CORE_ASSERT(false, "RendererAPI::None is not supported.");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return new OpenGLVertexArray();
  }

  DW_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace Dwarfworks
