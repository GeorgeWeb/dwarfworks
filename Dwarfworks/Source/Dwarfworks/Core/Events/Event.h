#ifndef CORE_EVENT_SYSTEM_EVENT_H_
#define CORE_EVENT_SYSTEM_EVENT_H_

#include "../Core.h"
#include "../Log/Log.h"
#include "dwpch.h"

namespace Dwarfworks {

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

/// \enum EventCategory
///
/// \brief Values that represent event categories.

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

/// \enum EventType
///
/// \brief Values that represent event types.

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
  AppLateUpdate,
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

/// \def EVENT_CLASS_TYPE(type)
///
/// \brief A macro that defines event class type.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param type The type.

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char* GetName() const override { return #type; }

/// \def EVENT_CLASS_CATEGORY(category)
///
/// \brief A macro that defines event class category.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param category The category.

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

/// \class Event
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API Event {
 public:
  /// \brief True if handled.
  bool IsHandled = false;

  /// \fn virtual EventType Event::GetEventType() const = 0;
  ///
  /// \brief Gets event type.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The event type.

  virtual EventType GetEventType() const = 0;

  /// \fn virtual const char* Event::GetName() const = 0;
  ///
  /// \brief Gets the name.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns Null if it fails, else the name.

  virtual const char* GetName() const = 0;

  /// \fn virtual int Event::GetCategoryFlags() const = 0;
  ///
  /// \brief Gets category flags.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The category flags.

  virtual int GetCategoryFlags() const = 0;

  /// \fn virtual std::string Event::ToString() const
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.

  virtual std::string ToString() const { return GetName(); }

  /// \fn inline bool Event::IsInCategory(EventCategory category) const
  ///
  /// \brief Query if 'category' is in category.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param category
  /// The category.
  ///
  /// \returns True if in category, false if not.

  // TODO: Rework the current design that uses unscoped enum!
  inline bool IsInCategory(EventCategory category) const {
    return GetCategoryFlags() & category;
  }

  /// \fn inline bool Event::CompareType(EventType type) const
  ///
  /// \brief Compare type.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param type
  /// The type.
  ///
  /// \returns True if it succeeds, false if it fails.

  inline bool CompareType(EventType type) const {
    return GetEventType() == type;
  }
};

/// \fn inline bool operator==(const Event& lhs, const Event& rhs)
///
/// \brief Equality operator.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param lhs The first instance to compare.
/// \param rhs
/// The second instance to compare.
///
/// \returns True if the parameters are considered equivalent.

inline bool operator==(const Event& lhs, const Event& rhs) {
  // check types
  return lhs.GetEventType() == rhs.GetEventType();
  // check names
  // && lhs.GetName() == rhs.GetName();
}

/// \fn inline std::ostream& operator<<(std::ostream& os, const Event& event) {
/// return os << event.ToString();
///
/// \brief Stream insertion operator.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param [in,out] os    The operating system.
/// \param 		    event
/// The event.
///
/// \returns The shifted result.

inline std::ostream& operator<<(std::ostream& os, const Event& event) {
  return os << event.ToString();
}

}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_H_
