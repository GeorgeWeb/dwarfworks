#ifndef EVENTS_EVENT_DISPATCHER_H
#define EVENTS_EVENT_DISPATCHER_H

#include "Event.h"

namespace Dwarfworks
{
// Events in Dwarfworks are currently blocking/synchronous. This means that when an event occurs it immediately gets
// dispatched and must be dealt with right then and there. For the future, a better strategy might be to buffer events
// in an event bus (a queue) and process them during the "event" part of the update stage.

class ENGINE_API EventDispatcher final
{
  public:
    explicit EventDispatcher(Event& event) : m_Event {event} {}

    // TryDispatch()
    template <typename TEvent, typename TFunction>
    constexpr void Dispatch(const TFunction& function)
    {
        if (m_Event.CompareType(TEvent::GetStaticType()))
        {
            bool handled = std::invoke(function, static_cast<TEvent&>(m_Event));
            m_Event.SetHandled(handled);
        }
    }

  private:
    Event& m_Event;
};

} // namespace Dwarfworks

#endif // EVENTS_EVENT_DISPATCHER_H
