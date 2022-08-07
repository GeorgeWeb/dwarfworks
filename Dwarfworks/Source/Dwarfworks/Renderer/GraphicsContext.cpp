// begin PCH
#include "dwpch.h"
// end PCH

#include "GraphicsContext.h"

#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

using namespace Dwarfworks;

GraphicsContext* GraphicsContext::Create(void* window)
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLContext(static_cast<GLFWwindow*>(window));
    }
}
