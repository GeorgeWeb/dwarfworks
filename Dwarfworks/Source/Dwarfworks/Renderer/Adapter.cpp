// begin PCH
#include "dwpch.h"
// end PCH

#include "Adapter.h"

#include "Dwarfworks/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLAdapter.h"

using namespace Dwarfworks;

Scope<Adapter> Adapter::Create()
{
    switch (Renderer::GetAPI())
    {
        default: DW_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateScope<OpenGLAdapter>();
    }
}
