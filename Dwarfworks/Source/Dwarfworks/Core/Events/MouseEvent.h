#ifndef CORE_EVENTS_MOUSE_EVENT_H_
#define CORE_EVENTS_MOUSE_EVENT_H_

#include "Event.h"

namespace Dwarfworks {

/// \class MouseMovedEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API MouseMovedEvent : public Event {
 public:
  /// \fn MouseMovedEvent::MouseMovedEvent(float x, float y)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param x The x coordinate.
  /// \param y The y coordinate.

  MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

  /// \fn inline float MouseMovedEvent::GetX() const
  ///
  /// \brief Get x coordinate.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The x coordinate.

  inline float GetX() const { return m_MouseX; }

  /// \fn inline float MouseMovedEvent::GetY() const
  ///
  /// \brief Get y coordinate.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The y coordinate.

  inline float GetY() const { return m_MouseY; }

  /// \fn std::string MouseMovedEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseMoved)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 private:
  /// \brief The mouse x coordinate.
  float m_MouseX;
  /// \brief The mouse y coordinate.
  float m_MouseY;
};

/// \class MouseScrolledEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API MouseScrolledEvent : public Event {
 public:
  /// \fn MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param xOffset The offset.
  /// \param yOffset The offset.

  MouseScrolledEvent(float xOffset, float yOffset)
      : m_XOffset(xOffset), m_YOffset(yOffset) {}

  /// \fn inline float MouseScrolledEvent::GetXOffset() const
  ///
  /// \brief Get x coordinate offset.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The x coordinate offset.

  inline float GetXOffset() const { return m_XOffset; }

  /// \fn inline float MouseScrolledEvent::GetYOffset() const
  ///
  /// \brief Get y coordinate offset.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The y coordinate offset.

  inline float GetYOffset() const { return m_YOffset; }

  /// \fn std::string MouseScrolledEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseScrolled)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 private:
  /// \brief The offset.
  float m_XOffset;
  /// \brief The offset.
  float m_YOffset;
};

/// \class MouseButtonEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API MouseButtonEvent : public Event {
 public:
  /// \fn inline int MouseButtonEvent::GetMouseButton() const
  ///
  /// \brief Gets mouse button.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The mouse button.

  inline int GetMouseButton() const { return m_Button; }

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 protected:
  /// \fn Dwarfworks::MouseButtonEvent::MouseButtonEvent(int button)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param button The button.

  MouseButtonEvent(int button) : m_Button(button) {}

  /// <summary>	The button. </summary>
  int m_Button;
};

/// \class MouseButtonPressedEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  /// \fn MouseButtonPressedEvent::MouseButtonPressedEvent(int button)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param button The button.

  MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

  /// \fn std::string MouseButtonPressedEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_Button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonPressed)
};

/// \class MouseButtonReleasedEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  /// \fn MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param button The button.

  MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  /// \fn std::string MouseButtonReleasedEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_Button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonReleased)
};

}  // namespace Dwarfworks

#endif  // CORE_EVENTS_MOUSE_EVENT_H_
