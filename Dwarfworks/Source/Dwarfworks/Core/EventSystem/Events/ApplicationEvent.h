#ifndef CORE_EVENT_SYSTEM_APPLICATION_EVENT_H_
#define CORE_EVENT_SYSTEM_APPLICATION_EVENT_H_

#include "../Event.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

// --------------------------
// Application Window Events
// --------------------------

class DW_API WindowCloseEvent
    : public EventT<WindowCloseEvent, EventCategory::Application> {
 public:
  WindowCloseEvent() = default;
};

class DW_API WindowResizeEvent
    : public EventT<WindowResizeEvent, EventCategory::Application> {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : m_Width(width), m_Height(height) {}

  std::string ToString() const {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
    return ss.str();
  }

 private:
  unsigned int m_Width, m_Height;
};

class DW_API WindowFocusEvent
    : public EventT<WindowFocusEvent, EventCategory::Application> {
 public:
  WindowFocusEvent() = default;

  std::string ToString() const { return GetName(); }
};

class DW_API WindowMovedEvent
    : public EventT<WindowMovedEvent, EventCategory::Application> {
 public:
  WindowMovedEvent() = default;

  std::string ToString() const { return GetName(); }
};

// ------------------------------
// Application (Game Loop) Events
// ------------------------------

class DW_API FixedUpdateEvent  // OnFixedUpdate (for physics)
    : public EventT<FixedUpdateEvent, EventCategory::Application> {
 public:
  FixedUpdateEvent() = default;

  std::string ToString() const { return GetName(); }
};

class DW_API UpdateEvent  // OnUpdate
    : public EventT<UpdateEvent, EventCategory::Application> {
 public:
  UpdateEvent() = default;

  std::string ToString() const { return GetName(); }
};

class DW_API RenderEvent  // OnRender
    : public EventT<RenderEvent, EventCategory::Application> {
 public:
  RenderEvent() = default;

  std::string ToString() const { return GetName(); }
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_APPLICATION_EVENT_H_
