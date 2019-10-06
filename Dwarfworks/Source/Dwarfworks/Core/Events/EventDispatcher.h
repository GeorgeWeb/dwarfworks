#ifndef CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
#define CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_

#include "Event.h"

namespace Dwarfworks {

// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

class DW_API EventManager {
  // commented out because we actually don't need a
  // heterogeneous collection of callable objects
  // using EventFn = std::function<bool(Event&)>;

 public:
  // TODO: Remove the current constructors and adapt the class
  // to be used as a "singleton"!
  explicit EventManager(Event& event) : m_Event(event) {}

  inline void Register(Event& event) { m_Event = event; }

  // EventFn will be (automatically) deduced by the compiler
  // lvalue event function
  template <typename EventT, typename EventFn>
  bool Dispatch(const EventFn& func) {
    if (m_Event.CompareType(EventT)) {
      m_Event.m_Handled = func(static_cast<EventFn>(m_Event));
      return true;
    }
    return false;
  }
  // rvalue event function
  template <typename EventT, typename EventFn>
  bool Dispatch(EventFn&& func) {
    if (m_Event.CompareType(EventT)) {
      m_Event.m_Handled = std::forward<EventFn>(
          func(static_cast<EventFn>(std::forward<EventT>(m_Event))));
      return true;
    }
    return false;
  }

 private:
  Event& m_Event;
};

}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
