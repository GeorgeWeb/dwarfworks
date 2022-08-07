#ifndef EVENTS_EVENT_H
#define EVENTS_EVENT_H

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Log/Log.h"

namespace Dwarfworks
{
// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

enum EventCategory
{
    None                     = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

enum class EventType : uint8_t
{
    None = 0,
    // Window Events
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    // Framebuffer Events
    FramebufferResize,
    // Application Events
    AppUpdate,
    // AppFixedUpdate,
    // AppLateUpdate,
    AppRender,
    // Keyboard Events
    KeyPressed,
    KeyReleased,
    KeyTyped,
    // Mouse Events
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType    GetStaticType() { return EventType::type; }                                                    \
    static bool         CompareStaticType(EventType cmpType) { return GetStaticType() == cmpType; }                    \
    virtual EventType   GetEventType() const override { return GetStaticType(); }                                      \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    virtual int GetCategoryFlags() const override { return category; }

class ENGINE_API Event
{
  public:
    Event();

    virtual EventType   GetEventType() const     = 0;
    virtual const char* GetName() const          = 0;
    virtual int         GetCategoryFlags() const = 0;

    bool CompareType(EventType type) const { return GetEventType() == type; }
    bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }

    virtual std::string ToString() const { return GetName(); }

    void SetHandled(bool handle) { m_IsHandled |= handle; }
    bool IsHandled() const { return m_IsHandled; }

  protected:
    bool m_IsHandled;
};

inline bool operator==(const Event& lhs, const Event& rhs)
{
    // Check if both events types are equal.
    // May want to check names as well but not considering for now.
    return lhs.GetEventType() == rhs.GetEventType();
}

inline std::ostream& operator<<(std::ostream& os, const Event& event)
{
    return os << event.ToString();
}

} // namespace Dwarfworks

#endif // EVENTS_EVENT_H
