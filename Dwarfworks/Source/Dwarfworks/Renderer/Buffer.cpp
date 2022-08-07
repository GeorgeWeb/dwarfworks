// begin PCH
#include "dwpch.h"
// end PCH

#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

using namespace Dwarfworks;

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, std::uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
    }
}

Ref<IndexBuffer> IndexBuffer::Create(std::uint32_t* indices, std::uint32_t count)
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
    }
}
