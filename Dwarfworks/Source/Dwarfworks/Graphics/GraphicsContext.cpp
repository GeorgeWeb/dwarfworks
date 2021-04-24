// begin PCH
#include "dwpch.h"
// end PCH

#include "GraphicsContext.h"

#include "Dwarfworks/Graphics/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

#ifdef DW_PLATFORM_WINDOWS
    #include "Platform/D3D12/D3D12Context.h"
#endif

namespace Dwarfworks
{
Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            DW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
#ifdef DW_PLATFORM_WINDOWS
        case RendererAPI::API::D3D12: return CreateScope<D3D12Context>(static_cast<GLFWwindow*>(window));
#endif
    }

    DW_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Dwarfworks
