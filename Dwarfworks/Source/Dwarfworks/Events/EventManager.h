#ifndef EVENTS_EVENT_MANAGER_H_
#define EVENTS_EVENT_MANAGER_H_

#include "Event.h"

namespace Dwarfworks
{
// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

class ENGINE_API EventManager
{
  public:
    // TODO: Remove the current constructors and re-design
    // the class to be used as a "singleton".
    explicit EventManager(Event& event) : m_Event(event) {}

    inline void Register(Event& event) { m_Event = event; }

    template <typename T, typename Func>
    bool Dispatch(const Func& fn)
    {
        if (m_Event.CompareType(T::GetStaticType()))
        {
            m_Event.IsHandled = fn(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }

  private:
    Event& m_Event;
};

} // namespace Dwarfworks

#endif // EVENTS_EVENT_MANAGER_H_
