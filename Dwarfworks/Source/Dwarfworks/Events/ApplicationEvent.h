#ifndef EVENTS_APPLICATION_EVENT_H_
#define EVENTS_APPLICATION_EVENT_H_

#include "Event.h"

namespace Dwarfworks {

// --------------------------
// Application Window Events
// --------------------------

/// \class WindowResizeEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API WindowResizeEvent : public Event {
 public:
  /// \fn WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int
  /// height)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param width  The width.
  /// \param height The height.

  WindowResizeEvent(unsigned int width, unsigned int height)
      : m_Width(width), m_Height(height) {}

  /// \fn inline unsigned int WindowResizeEvent::GetWidth() const
  ///
  /// \brief Gets the width.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The width.

  inline unsigned int GetWidth() const { return m_Width; }

  /// \fn inline unsigned int WindowResizeEvent::GetHeight() const
  ///
  /// \brief Gets the height.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The height.

  inline unsigned int GetHeight() const { return m_Height; }

  /// \fn std::string WindowResizeEvent::ToString() const override
  ///
  /// \brief Convert this object into a string representation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A std::string that represents this object.

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
 private:
  /// \brief The width.
  unsigned int m_Width;
  /// \brief The height.
  unsigned int m_Height;
};

/// \class WindowCloseEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API WindowCloseEvent : public Event {
 public:
  /// \fn WindowCloseEvent::WindowCloseEvent() = default;
  ///
  /// \brief Default constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  WindowCloseEvent() = default;

  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

// ------------------------------
// Application (Game Loop) Events
// ------------------------------

/// \class AppFixedUpdateEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API AppFixedUpdateEvent : public Event {
 public:
  /// \fn AppFixedUpdateEvent::AppFixedUpdateEvent() = default;
  ///
  /// \brief Default constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  AppFixedUpdateEvent() = default;

  EVENT_CLASS_TYPE(AppFixedUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class DW_API AppUpdateEvent : public Event {
 public:
  /// \fn AppUpdateEvent::AppUpdateEvent() = default;
  ///
  /// \brief Default constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  AppUpdateEvent() = default;

  EVENT_CLASS_TYPE(AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

/// \class AppUpdateEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API AppLateUpdateEvent : public Event {
 public:
  /// \fn AppUpdateEvent::AppUpdateEvent() = default;
  ///
  /// \brief Default constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  AppLateUpdateEvent() = default;

  EVENT_CLASS_TYPE(AppLateUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

/// \class AppRenderEvent
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API AppRenderEvent : public Event {
 public:
  /// \fn AppRenderEvent::AppRenderEvent() = default;
  ///
  /// \brief Default constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  AppRenderEvent() = default;

  EVENT_CLASS_TYPE(AppRender)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}  // namespace Dwarfworks

#endif  // EVENTS_APPLICATION_EVENT_H_
