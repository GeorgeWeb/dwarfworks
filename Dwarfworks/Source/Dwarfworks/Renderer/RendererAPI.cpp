// begin PCH
#include "dwpch.h"
// end PCH

#include "RendererAPI.h"

namespace Dwarfworks
{
#if PLATFORM_WINDOWS
ENGINE_API RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
#elif PLATFORM_MACOS
ENGINE_API RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
#elif PLATFORM_LINUX
ENGINE_API RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
#else
    #error "Supported rendering API for this platform is not yet implemented!"
#endif
} // namespace Dwarfworks
