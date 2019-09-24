#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_MOUSE_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_MOUSE_EVENT_H_

#include "../Event.h"

#include <sstream>

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

class DWARF_API MouseMovedEvent
    : public EventT<MouseMovedEvent,
                    EventCategory::Mouse | EventCategory::Input> {
 public:
  MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

  inline float GetX() const noexcept { return m_MouseX; }
  inline float GetY() const noexcept { return m_MouseY; }

  std::string ToString() const {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
    return ss.str();
  }

 private:
  float m_MouseX;
  float m_MouseY;
};

class DWARF_API MouseScrolledEvent
    : public EventT<MouseScrolledEvent,
                    EventCategory::Mouse | EventCategory::Input> {
 public:
  MouseScrolledEvent(float xOffset, float yOffset)
      : m_XOffset(xOffset), m_YOffset(yOffset) {}

  inline float GetXOffset() const noexcept { return m_XOffset; }
  inline float GetYOffset() const noexcept { return m_YOffset; }

  std::string ToString() const {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
    return ss.str();
  }

 private:
  float m_XOffset;
  float m_YOffset;
};

template <class MouseButtonEventType>
class DWARF_API MouseButtonEvent
    : public EventT<MouseButtonEvent<MouseButtonEventType>,
                    EventCategory::Mouse | EventCategory::Input> {
 public:
  inline float GetButton() const noexcept { return m_Button; }
  // inline void SetButton(int button) noexcept { m_Button = button; }

 protected:
  // MouseButtonEvent() = default;
  explicit MouseButtonEvent(float button) : m_Button(button) {}

  int m_Button;
};

class DWARF_API MouseButtonPressedEvent
    : public MouseButtonEvent<MouseButtonPressedEvent> {
 public:
  explicit MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_Button;
    return ss.str();
  }
};

class DWARF_API MouseButtonReleasedEvent
    : public MouseButtonEvent<MouseButtonReleasedEvent> {
 public:
  explicit MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_Button;
    return ss.str();
  }
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // !DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_MOUSE_EVENT_H_
