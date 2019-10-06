#ifndef CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
#define CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_

#include "Event.h"

namespace Dwarfworks {
namespace Core {

// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

class DW_API EventDispatcher {
  // commented out because we actually don't need a
  // heterogeneous collection of callable objects
  // using EventFn = std::function<bool(Event&)>;

 public:
  explicit EventDispatcher(Event& event) : m_Event(event) {}

  inline void Register(Event& event) { m_Event = event; }

  // EventFn will be (automatically) deduced by the compiler
  template <typename EventT, typename EventFn>
  bool Dispatch(const EventFn& func) {
    if (m_Event.CompareType(EventT)) {
      m_Event.m_Handled = func(static_cast<EventT&>(m_Event));
      return true;
    }
    return false;
  }

 private:
  Event& m_Event;
};

}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
