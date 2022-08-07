#ifndef EVENTS_KEY_EVENT_H
#define EVENTS_KEY_EVENT_H

#include "Event.h"

namespace Dwarfworks
{
// ---------------------
// Keyboard Input Events
// ---------------------

class ENGINE_API KeyEvent : public Event
{
  public:
    inline int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
  protected:
    explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

class ENGINE_API KeyPressedEvent : public KeyEvent
{
  public:
    KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

    inline int GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(KeyPressed)
  private:
    int m_RepeatCount;
};

class ENGINE_API KeyReleasedEvent : public KeyEvent
{
  public:
    explicit KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    std::string ToString() const override;

    EVENT_CLASS_TYPE(KeyReleased)
};

class ENGINE_API KeyTypedEvent : public KeyEvent
{
  public:
    explicit KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

    std::string ToString() const override;

    EVENT_CLASS_TYPE(KeyTyped)
};

} // namespace Dwarfworks

#endif // EVENTS_KEY_EVENT_H
