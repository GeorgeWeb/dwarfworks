// begin PCH
#include "dwpch.h"
// end PCH

#include "KeyEvent.h"

using namespace Dwarfworks;

std::string KeyPressedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
    return ss.str();
}

std::string KeyReleasedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
}

std::string KeyTypedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyTypedEvent: " << m_KeyCode;
    return ss.str();
}
