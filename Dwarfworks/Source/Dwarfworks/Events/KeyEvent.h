#ifndef EVENTS_KEY_EVENT_H_
#define EVENTS_KEY_EVENT_H_

#include "Event.h"

namespace Dwarfworks {

// ---------------------
// Keyboard Input Events
// ---------------------

class DW_API KeyEvent : public Event {
 public:
  inline int GetKeyCode() const { return m_KeyCode; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
 protected:
  explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}

  int m_KeyCode;
};

class DW_API KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(int keycode, int repeatCount)
      : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

  inline int GetRepeatCount() const { return m_RepeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)
 private:
  int m_RepeatCount;
};

class DW_API KeyReleasedEvent : public KeyEvent {
 public:
  explicit KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

class DW_API KeyTypedEvent : public KeyEvent {
 public:
  explicit KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyTyped)
};

}  // namespace Dwarfworks

#endif  // EVENTS_KEY_EVENT_H_
