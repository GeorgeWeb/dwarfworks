#ifndef CORE_EVENTS_APPLICATION_EVENT_H_
#define CORE_EVENTS_APPLICATION_EVENT_H_

#include "Event.h"

namespace Dwarfworks {

// --------------------------
// Application Window Events
// --------------------------

class DW_API WindowResizeEvent : public Event {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : m_Width(width), m_Height(height) {}

  inline unsigned int GetWidth() const { return m_Width; }
  inline unsigned int GetHeight() const { return m_Height; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
 private:
  unsigned int m_Width, m_Height;
};

class DW_API WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() {}

  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

// ------------------------------
// Application (Game Loop) Events
// ------------------------------

class DW_API AppFixedUpdateEvent : public Event {
 public:
  AppFixedUpdateEvent() {}

  EVENT_CLASS_TYPE(AppFixedUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class DW_API AppUpdateEvent : public Event {
 public:
  AppUpdateEvent() {}

  EVENT_CLASS_TYPE(AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class DW_API AppRenderEvent : public Event {
 public:
  AppRenderEvent() {}

  EVENT_CLASS_TYPE(AppRender)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}  // namespace Dwarfworks

#endif  // CORE_EVENTS_APPLICATION_EVENT_H_
