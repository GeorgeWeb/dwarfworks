#ifndef CORE_EVENT_SYSTEM_EVENT_H_
#define CORE_EVENT_SYSTEM_EVENT_H_

#include "dwpch.h"

#include "../Core.h"
#include "../Logging/Log.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

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
struct DW_API EventCategory {
  using Type = int;  // ...
  static constexpr Type Uncategorized = 0;
  static constexpr Type Application = BIT(0);
  static constexpr Type Input = BIT(1);
  static constexpr Type Keyboard = BIT(2);
  static constexpr Type Mouse = BIT(3);
  static constexpr Type MouseButton = BIT(4);
};
// alias
using EventCategoryT = EventCategory::Type;
}  // namespace

// ------------
// Event Types:
// ------------
// Uncategorized
// Application: WindowClose, WindowResize, WindowFocus, WindowMoved
// Application: FixedUpdate, Update, Render
// Keyboard | Input: KeyPressed, KeyReleased
// Mouse | Input: MouseMoved, MouseScrolled
// MouseButton | Mouse | Input: MouseButtonPressed, MouseButtonReleased,

template <class EventTypeLhs, class EventTypeRhs>
bool operator==(EventTypeLhs, EventTypeRhs);

template <class EventType, EventCategoryT Category>
class DW_API EventT : public CRTP<EventType> {
  template <class>
  friend class EventDispatcher;

  template <class EventTypeLhs, class EventTypeRhs>
  friend bool operator==(EventTypeLhs, EventTypeRhs);

 public:
  // for debugging purposes mostly
  std::string GetName() const noexcept {
    // TODO: use boost::core::demangle to produce a more human-readable output
    return typeid(this->Implementation()).name();
  }
  std::string ToString() const { return this->Implementation().ToString(); }

  inline EventCategoryT GetCategoryFlags() const noexcept { return Category; }
  inline bool IsInCategory(EventCategoryT category) const noexcept {
    return GetCategoryFlags() & category;
  }

  EventType GetEventType() const noexcept { return this->Implementation(); }

  // compare object against another object based on type
  template <class ComparisonEventType>
  inline bool Compare(ComparisonEventType event) {
    return std::is_same_v<decltype(this->Implementation().GetEventType()),
                          decltype(event.GetEventType())>;
  }

  // compare object type against another object type
  template <typename OtherEventType>
  inline bool CompareType() {
    return std::is_same_v<decltype(this->implementation.GetEventType()),
                          OtherEventType>;
  }

 protected:
  bool m_IsHandled{false};
};

template <class EventTypeLhs, class EventTypeRhs>
bool operator==(EventTypeLhs eventLhs, EventTypeRhs eventRhs) {
  return eventLhs.Compare(eventRhs);
}

template <class EventType, EventCategoryT Category>
inline std::ostream& operator<<(std::ostream& os,
                                EventT<EventType, Category> const& event) {
  return os << event.ToString();
}

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_H_
