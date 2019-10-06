#ifndef CORE_EVENT_SYSTEM_EVENT_H_
#define CORE_EVENT_SYSTEM_EVENT_H_

#include "dwpch.h"

#include "../Core.h"
#include "../Log/Log.h"

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
// Each category is represented as a bit that is set in a bitfield to define
// the category of an event
enum EventCategory {
  None = 0,
  EventCategoryApplication = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4)
};

// ------------
// Event Types:
// ------------
enum class EventType {
  None = 0,
  // Window Events
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  // Application Events
  AppFixedUpdate,
  AppUpdate,
  AppRender,
  // Input: Keyboard Events
  KeyPressed,
  KeyReleased,
  KeyTyped,
  // Input: Mouse Events
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

class DW_API Event {
 public:
  bool Handled = false;

  virtual EventType GetEventType() const = 0;
  virtual const char* GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); }

  inline bool IsInCategory(EventCategory category) const {
    return GetCategoryFlags() & category;
  }

  inline bool CompareType(EventType type) const {
    return GetEventType() == type;
  }
};

inline bool operator==(const Event& lhs, const Event& rhs) {
  return
      // check types
      lhs.GetEventType() == rhs.GetEventType()
      // check names
      && lhs.GetName() == rhs.GetName();
}

inline std::ostream& operator<<(std::ostream& os, const Event& event) {
  return os << event.ToString();
}

}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_H_
