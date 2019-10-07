#ifndef CORE_EVENTS_KEY_EVENT_H_
#define CORE_EVENTS_KEY_EVENT_H_

#include "Event.h"

namespace Dwarfworks {

// ---------------------
// Keyboard Input Events
// ---------------------

/// \class KeyEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API KeyEvent : public Event {
 public:
  /// \fn inline int KeyEvent::GetKeyCode() const
  ///
  /// \brief Gets key code.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The key code.
  ///
  /// \returns The key code.

  inline int GetKeyCode() const { return m_KeyCode; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
 protected:
  /// \fn Dwarfworks::KeyEvent::KeyEvent(int keycode)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param keycode The keycode.

  KeyEvent(int keycode) : m_KeyCode(keycode) {}

  /// \brief The key code.
  int m_KeyCode;
};

/// \class KeyPressedEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API KeyPressedEvent : public KeyEvent {
 public:
  /// \fn KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param keycode	 The keycode.
  /// \param repeatCount Number of repeats.

  KeyPressedEvent(int keycode, int repeatCount)
      : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

  /// \fn inline int KeyPressedEvent::GetRepeatCount() const
  ///
  /// \brief Gets repeat count.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The repeat count.
  ///
  /// \returns The repeat count.

  inline int GetRepeatCount() const { return m_RepeatCount; }

  /// \fn std::string KeyPressedEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)
 private:
  /// \brief Number of repeats.
  int m_RepeatCount;
};

/// \class KeyReleasedEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API KeyReleasedEvent : public KeyEvent {
 public:
  /// \fn KeyReleasedEvent::KeyReleasedEvent(int keycode)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param keycode The keycode.

  KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

  /// \fn std::string KeyReleasedEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

/// \class KeyTypedEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API KeyTypedEvent : public KeyEvent {
 public:
  /// \fn KeyTypedEvent::KeyTypedEvent(int keycode)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param keycode The keycode.

  KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

  /// \fn std::string KeyTypedEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyTyped)
};

}  // namespace Dwarfworks

#endif  // CORE_EVENTS_KEY_EVENT_H_
