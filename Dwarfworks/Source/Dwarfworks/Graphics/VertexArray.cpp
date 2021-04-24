// begin PCH
#include "dwpch.h"
// end PCH

#include "VertexArray.h"
#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dwarfworks
{
Ref<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None: DW_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
    }

    DW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Dwarfworks
