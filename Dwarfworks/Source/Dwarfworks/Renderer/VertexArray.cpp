// begin PCH
#include "dwpch.h"
// end PCH

#include "VertexArray.h"
#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

using namespace Dwarfworks;

Ref<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
    }
}
