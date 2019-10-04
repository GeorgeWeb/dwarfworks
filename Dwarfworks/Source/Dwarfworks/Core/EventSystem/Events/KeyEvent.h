#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_KEY_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_KEY_EVENT_H_

#include "../Event.h"

#include <sstream>

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

// ---------------------
// Keyboard Input Events
// ---------------------

template <class KeyEventType>
class DWARF_API KeyEvent
    : public EventT<KeyEvent<KeyEventType>,
                    EventCategory::Keyboard | EventCategory::Input> {
 public:
  KeyEvent() = default;

  std::string ToString() const { return GetName(); }

  inline int GetKeyCode() const noexcept { return m_KeyCode; }

 protected:
  int m_KeyCode;
};

struct DWARF_API KeyPressedEvent : public KeyEvent<KeyPressedEvent> {
 public:
  KeyPressedEvent() = default;

  std::string ToString() const {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

  inline int GetRepeatCount() const noexcept { return m_RepeatCount; }

 private:
  int m_RepeatCount;
};

struct DWARF_API KeyReleasedEvent : public KeyEvent<KeyReleasedEvent> {
 public:
  KeyReleasedEvent() = default;

  std::string ToString() const {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
  }
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // !DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_KEY_EVENT_H_
