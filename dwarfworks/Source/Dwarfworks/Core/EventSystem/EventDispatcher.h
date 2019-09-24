#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_

#include "Event.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

template <class Event>
class EventDispatcher {
  template <class EventType>
  using EventFn = std::function<bool(EventType&)>;

 public:
  explicit EventDispatcher(Event& event) : m_Event(event) {}

  template <class EventType>
  inline bool Dispatch(EventFn<EventType> func) {
    if (m_Event.EqualsType(EventType)) {
      DWARF_CORE_INFO("The events are of the same type.");
      m_Event.m_Handled = func(m_Event);
      return true;
    }
    return false;
  }

 private:
  Event m_Event;
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
