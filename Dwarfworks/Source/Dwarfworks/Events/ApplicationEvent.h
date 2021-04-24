#ifndef EVENTS_APPLICATION_EVENT_H_
#define EVENTS_APPLICATION_EVENT_H_

#include "Event.h"

namespace Dwarfworks
{
// ---------------------------
// Application (Window) Events
// ---------------------------

class ENGINE_API WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ENGINE_API WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

    inline uint32_t GetWidth() const { return m_Width; }
    inline uint32_t GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent:\t" << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  private:
    // width and height of the window
    uint32_t m_Width, m_Height;
};

// ---------------------------------
// Application (Frame Buffer) Events
// ---------------------------------

class ENGINE_API FramebufferResizeEvent : public Event
{
  public:
    FramebufferResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

    inline uint32_t GetWidth() const { return m_Width; }
    inline uint32_t GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "FramebufferResizeEvent:\t" << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(FramebufferResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  private:
    // width and height of the viewport
    uint32_t m_Width, m_Height;
};

// ------------------------------
// Application (Game Loop) Events
// ------------------------------

class ENGINE_API AppFixedUpdateEvent : public Event
{
  public:
    AppFixedUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppFixedUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ENGINE_API AppUpdateEvent : public Event
{
  public:
    AppUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ENGINE_API AppLateUpdateEvent : public Event
{
  public:
    AppLateUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppLateUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ENGINE_API AppRenderEvent : public Event
{
  public:
    AppRenderEvent() = default;

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // namespace Dwarfworks

#endif // EVENTS_APPLICATION_EVENT_H_
