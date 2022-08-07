// begin PCH
#include "dwpch.h"
// end PCH

#include "RenderCommand.h"

// Temp.
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Dwarfworks
{
#if PLATFORM_WINDOWS
ENGINE_API Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
#elif PLATFORM_MACOS
ENGINE_API Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
#elif PLATFORM_LINUX
ENGINE_API Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
#else
    #error "Supported rendering API for this platform is not yet implemented!"
#endif
} // namespace Dwarfworks
