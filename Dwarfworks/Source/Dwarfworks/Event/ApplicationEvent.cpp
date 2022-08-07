// begin PCH
#include "dwpch.h"
// end PCH

#include "ApplicationEvent.h"

using namespace Dwarfworks;

std::string WindowResizeEvent::ToString() const
{
    std::stringstream ss;
    ss << "WindowResizeEvent:\t" << m_WindowWidth << ", " << m_WindowHeight;
    return ss.str();
}

std::string FramebufferResizeEvent::ToString() const
{
    std::stringstream ss;
    ss << "FramebufferResizeEvent:\t" << m_ViewportWidth << ", " << m_ViewportHeight;
    return ss.str();
}
