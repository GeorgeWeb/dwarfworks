#ifndef CORE_WINDOW_WINDOW_H_
#define CORE_WINDOW_WINDOW_H_

#include "dwpch.h"

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Events/EventManager.h"

namespace Dwarfworks {

/// \struct WindowProps
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

struct DW_API WindowProps {
  /// \brief The title
  std::string Title;
  /// \brief The width
  unsigned int Width;
  /// \brief The height
  unsigned int Height;

  /// \fn explicit WindowProps(const std::string& title = "Dwarfworks Engine",
  /// unsigned int width = 1280, unsigned int height = 720)
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param title  (Optional) The title.
  /// \param width  (Optional) The width.
  /// \param height (Optional) The height.

  explicit WindowProps(const std::string& title = "Dwarfworks Engine",
                       unsigned int width = 1280, unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
};

//
// Implemented per platform

/// \class Window
///
/// \brief Interface representing a desktop system based window. Implemented per
/// platform
///
/// \author Georg
/// \date 07/10/2019

class DW_API IWindow {
 public:
  /// \brief The event callback function.
  using EventCallbackFn = std::function<void(Event&)>;

  // CRTP or no CRTP, we need the virtual destructor

  /// \fn virtual Window::~Window() = default;
  ///
  /// \brief Destructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual ~IWindow() = default;

  /// \fn virtual void Window::OnUpdate() = 0;
  ///
  /// \brief Executes the update action.
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual void OnUpdate() = 0;

  /// \fn virtual unsigned int Window::GetWidth() const = 0;
  ///
  /// \brief Gets the width.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The width.

  virtual unsigned int GetWidth() const = 0;

  /// \fn virtual unsigned int Window::GetHeight() const = 0;
  ///
  /// \brief Gets the height.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The height.

  virtual unsigned int GetHeight() const = 0;

  // Window attributes

  /// \fn virtual void Window::SetEventCallback(const EventCallbackFn& callback)
  /// = 0;
  ///
  /// \brief Callback, called when the set event.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param callback The callback.

  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

  /// \fn virtual void Window::SetVSync(bool isEnabled) = 0;
  ///
  /// \brief Sets v synchronise.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param isEnabled True if is enabled, false if not.

  virtual void SetVSync(bool isEnabled) = 0;

  /// \fn virtual bool Window::IsVSync() const = 0;
  ///
  /// \brief Query if this object is v synchronise.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns True if v synchronise, false if not.

  virtual bool IsVSync() const = 0;

  /// \fn virtual void* Window::GetNativeWindow() const = 0;
  ///
  /// \brief Gets native window
  ///
  /// \author Georg
  /// \date 12/10/2019
  ///
  /// \returns Null if it fails, else the native window.

  virtual void* GetNativeWindow() const = 0;

  /// \fn static Window* Window::Create(const WindowProps& props =
  /// WindowProps{});
  ///
  /// \brief Creates a new Window*.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param props (Optional) The properties.
  ///
  /// \returns Null if it fails, else a pointer to a Window.

  static IWindow* Create(const WindowProps& props = WindowProps{});
};

}  // namespace Dwarfworks

#endif  // CORE_WINDOW_WINDOW_H_
