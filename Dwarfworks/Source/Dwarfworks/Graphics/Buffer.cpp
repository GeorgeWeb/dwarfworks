// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Dwarfworks {

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      DW_CORE_ASSERT(false, "RendererAPI::None is not supported.");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return new OpenGLVertexBuffer(vertices, size);
  }

  DW_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      DW_CORE_ASSERT(false, "RendererAPI::None is not supported.");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return new OpenGLIndexBuffer(indices, count);
  }

  DW_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}  // namespace Dwarfworks
