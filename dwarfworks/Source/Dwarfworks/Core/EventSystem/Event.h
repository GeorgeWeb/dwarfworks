#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_H_

#include "../Core.h"
#include "../Log.h"

#include <algorithm>
#include <functional>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace Dwarfworks {
namespace Core {

// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

// -----------------
// Event Categories:
// -----------------
// Uncategorized, Application, Input, Keyboard, Mouse, MouseButton

namespace {
// Each category is represented as a bit that is set in a bitfield to define
// the category of an event
struct DWARF_API EventCategory {
  using Type = int;  // ...
  static constexpr Type Uncategorized = 0;
  static constexpr Type Application = BIT(0);
  static constexpr Type Input = BIT(1);
  static constexpr Type Keyboard = BIT(2);
  static constexpr Type Mouse = BIT(3);
};
// alias
using EventCategoryT = EventCategory::Type;
}  // namespace

// ------------
// Event Types:
// ------------
// Uncategorized
// [Application] Window: WindowClose, WindowResize, WindowFocus, WindowMoved,
// [Application] Application: AppTick, AppUpdate, AppRender
// [Input] Keyboard: KeyPressed, KeyReleased
// [Input] Mouse: MouseButtonPressed, MouseButtonReleased
// [Input] MouseButton: MouseMoved, MouseScrolled

// Dispatch => Handle
// EventDispatcher => EventHandler

// prototype of the Event class
// template <class EventType, EventCategoryT Category>
// class EventT;

// prototype of the equality operator for Event
template <class EventLhs, class EventRhs>
bool operator==(EventLhs, EventRhs);

template <class EventType, EventCategoryT Category>
class DWARF_API EventT : public CRTP<EventType> {
  template <class Event>
  friend class EventDispatcher;

  // ...
  template <class EventLhs, class EventRhs>
  friend bool operator==<>(EventLhs, EventRhs);

 public:
  // for debugging purposes mostly
  EventType GetEventType() const noexcept { return this->Implementation(); }
  std::string GetName() const noexcept {
    // TODO: use boost::core::demangle to produce a more human-readable output
    return typeid(this->Implementation()).name();
  }
  std::string ToString() const { return this->Implementation().ToString(); }

  template <class OtherEvent>
  inline bool IsSameAs(OtherEvent event) {
    return std::is_same_v<decltype(this->Implementation().GetEventType()),
                          decltype(event.GetEventType())>;
  }

  // ...
  template <typename OtherEventType>
  inline bool EqualsType() {
    return std::is_same_v<decltype(this->implementation.GetEventType()),
                          OtherEventType>;
  }

  // ...
  inline EventCategoryT GetCategoryFlags() const noexcept { return Category; }
  inline bool IsInCategory(EventCategoryT category) const noexcept {
    return GetCategoryFlags() & category;
  }

 protected:
  bool m_IsHandled = false;
};

// ...
template <class EventLhs, class EventRhs>
bool operator==<>(EventLhs eventLhs, EventRhs eventRhs) {
  if (eventLhs.IsSameAs(eventRhs)) {
    DWARF_CORE_INFO("Hooray, event types match.");
    return true;
  }
  DWARF_CORE_WARN("Oopsie, event types do not match.");
  return false;
}

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

}  // namespace Core
}  // namespace Dwarfworks

#endif  // DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_H_
