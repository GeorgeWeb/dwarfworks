#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_H_

#include "../Core.h"
#include "../Log.h"

#include <algorithm>
#include <functional>
#include <string>
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

// Each category is represented as a bit that is set in a bitfield to define
// the category of an event
namespace EventCategoryFlags {
static constexpr int Uncategorized = 0;
static constexpr int Application = BIT(0);
static constexpr int Input = BIT(1);
static constexpr int Keyboard = BIT(2);
static constexpr int Mouse = BIT(3);
}  // namespace EventCategoryFlags

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

// ...
template <typename EventType, int CategoryFlags>
class DWARF_API EventT : public CRTP<EventType> {
  // ...
  template <typename EventType>
  friend class EventDispatcher;

 public:
  // ...
  EventType const& GetType() const { return this->Implementation(); }
  // ...
  std::string GetName() const { return typeid(this->Implementation()).name(); }

  // ...
  int GetCategoryFlags() const {
    return Category;
    // return this->Implementation().GetCategoryFlags();
  }

  inline bool IsInCategory(int category) const {
    return GetCategoryFlags() & category;
  }

  // dispatching
  // void Dispatch() const { this->Implementation().Dispatch(); }

 protected:
  bool m_Handled;
};

}  // namespace Core
}  // namespace Dwarfworks

#endif  // DWARFWORKS_CORE_EVENT_SYSTEM_EVENT_H_
