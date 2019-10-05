#ifndef CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
#define CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_

#include "Event.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

template <class EventType>
class DW_API EventDispatcher {
  template <class DispEventType>
  using EventFn = std::function<bool(DispEventType&)>;

 public:
  explicit EventDispatcher(EventType& event) : m_Event(event) {}

  template <class DispEventType>
  inline bool Dispatch(EventFn<DispEventType> func) {
    if (m_Event.CompareType(DispEventType)) {
      handleEvent(func);
      return true;
    }
    return false;
  }

 private:
  EventType m_Event;

  template <class DispEventType>
  void handleEvent(EventFn<DispEventType> func) {
    m_Event.m_Handled = func(m_Event);
  }
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
