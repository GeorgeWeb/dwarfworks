// begin PCH
#include "dwpch.h"
// end PCH

#include "Window.h"

#ifdef PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsWindow.h"
#elif defined(PLATFORM_MACOS)
    #include "Platform/Mac/MacWindow.h"
#elif defined(PLATFORM_LINUX)
    #include "Platform/Linux/LinuxWindow.h"
#endif

namespace Dwarfworks
{
Scope<Window> Window::Create(const WindowProps& props)
{
#ifdef PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#elif defined(PLATFORM_MACOS)
    return CreateScope<MacWindow>(props);
#elif defined(PLATFORM_LINUX)
    return CreateScope<LinuxWindow>(props);
#else
    HZ_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
}

} // namespace Dwarfworks
