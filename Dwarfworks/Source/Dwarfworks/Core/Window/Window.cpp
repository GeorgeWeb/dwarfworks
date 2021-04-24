// begin PCH
#include "dwpch.h"
// end PCH

#include "Window.h"

#ifdef DW_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsWindow.h"
#elif defined(DW_PLATFORM_LINUX)
    #include "Platform/Linux/LinuxWindow.h"
#endif

namespace Dwarfworks
{
Scope<Window> Window::Create(const WindowProps& props)
{
#ifdef DW_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#elif defined(DW_PLATFORM_LINUX)
    // TODO: Check if LinuxWindow is up-to-date
    return CreateScope<LinuxWindow>(props);
#else
    HZ_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
}

} // namespace Dwarfworks
