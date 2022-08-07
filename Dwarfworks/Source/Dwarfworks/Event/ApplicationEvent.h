#ifndef EVENTS_APPLICATION_EVENT_H
#define EVENTS_APPLICATION_EVENT_H

#include "Event.h"

namespace Dwarfworks
{
// ---------------------------
// Application (Window) Events
// ---------------------------

class ENGINE_API WindowCloseEvent final : public Event
{
  public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ENGINE_API WindowResizeEvent final : public Event
{
  public:
    explicit WindowResizeEvent(uint32_t width, uint32_t height) : m_WindowWidth {width}, m_WindowHeight {height} {}

    uint32_t GetWidth() const { return m_WindowWidth; }
    uint32_t GetHeight() const { return m_WindowHeight; }

    std::string ToString() const override final;

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  private:
    uint32_t m_WindowWidth;
    uint32_t m_WindowHeight;
};

class ENGINE_API FramebufferResizeEvent final : public Event
{
  public:
    explicit FramebufferResizeEvent(uint32_t width, uint32_t height)
        : m_ViewportWidth {width}, m_ViewportHeight {height}
    {
    }

    uint32_t GetWidth() const { return m_ViewportWidth; }
    uint32_t GetHeight() const { return m_ViewportHeight; }

    std::string ToString() const override final;

    EVENT_CLASS_TYPE(FramebufferResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
  private:
    uint32_t m_ViewportWidth;
    uint32_t m_ViewportHeight;
};

class ENGINE_API AppUpdateEvent final : public Event
{
  public:
    AppUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ENGINE_API AppRenderEvent final : public Event
{
  public:
    AppRenderEvent() = default;

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // namespace Dwarfworks

#endif // EVENTS_APPLICATION_EVENT_H
