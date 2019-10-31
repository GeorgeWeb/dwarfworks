#ifndef CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
#define CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_

#include "Event.h"

namespace Dwarfworks {

// Events in Dwarfworks are currently blocking or synchronous.
// This means that when an event occurs it immediately gets dispatched
// and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event bus
// (a queue) and process them during the "event" part of the update stage.

/// \class EventManager
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API EventManager {
  // commented out because we actually don't need a
  // heterogeneous collection of callable objects
  // using EventFn = std::function<bool(Event&)>;

 public:
  // TODO: Remove the current constructors and adapt the class
  // to be used as a "singleton"!

  /// \fn explicit EventManager::EventManager(Event& event)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] event The event.

  explicit EventManager(Event& event) : m_Event(event) {}

  /// \fn inline void EventManager::Register(Event& event)
  ///
  /// \brief Registers this object.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] event The event.

  inline void Register(Event& event) { m_Event = event; }

  // Event functions (EventFn) will be (automatically) deduced by the compiler

  /// \fn template <typename EventT, typename EventFn> bool
  /// EventManager::Dispatch(const EventFn& func)
  ///
  /// \brief Dispatches the given function (l-value event function)..
  ///
  /// \typeparam EventT  Type of the event.
  /// \typeparam EventFn Type of the event function.
  /// \param func The function.
  ///
  /// \returns True if it succeeds, false if it fails.

  template <typename EventT, typename EventFn>
  bool Dispatch(const EventFn& func) {
    if (m_Event.CompareType(EventT::GetStaticType())) {
      m_Event.IsHandled = func(static_cast<EventT&>(m_Event));
      return true;
    }
    return false;
  }

 private:
  /// \brief The event.
  Event& m_Event;
};

}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENT_DISPATCHER_H_
