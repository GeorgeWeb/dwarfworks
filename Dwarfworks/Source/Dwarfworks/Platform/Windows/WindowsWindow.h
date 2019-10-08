#ifndef PLATFORM_WINDOWS_WINDOW_H_
#define PLATFORM_WINDOWS_WINDOW_H_

#include "../../Core/Window/Window.h"

/// \struct GLFWwindow
///
/// \brief Form for viewing the GLFWwindow.
///
/// \author Georg
/// \date 07/10/2019

struct GLFWwindow;
// Note: This forward declaration is used so we avoid include the glfw3.h header
// just for declaring a GLFWwindow* member of the WindowsWindow class and also
// avoid errors for the order of inclusion of their headers (glad.h is first).

namespace Dwarfworks {

/// \class WindowsWindow
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API WindowsWindow : public Window {
 public:
  /// \fn explicit WindowsWindow::WindowsWindow(const WindowProps& props);
  ///
  /// \brief Constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param props The properties.

  explicit WindowsWindow(const WindowProps& props);

  /// \fn virtual WindowsWindow::~WindowsWindow();
  ///
  /// \brief Destructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual ~WindowsWindow();

  /// \fn void WindowsWindow::OnUpdate() override;
  ///
  /// \brief Executes the update action.
  ///
  /// \author Georg
  /// \date 07/10/2019

  void OnUpdate() override;

  /// \fn unsigned int WindowsWindow::GetWidth() const override
  ///
  /// \brief Gets the width.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The width.

  unsigned int GetWidth() const override { return m_Data.Width; }

  /// \fn unsigned int WindowsWindow::GetHeight() const override
  ///
  /// \brief Gets the height.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The height.

  unsigned int GetHeight() const override { return m_Data.Height; }

  // Window attributes

  /// \fn void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
  /// override;
  ///
  /// \brief Callback, called when the set event.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param callback The callback.

  void SetEventCallback(const EventCallbackFn& callback) override;

  /// \fn void WindowsWindow::SetVSync(bool isEnabled) override;
  ///
  /// \brief Sets v synchronise.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param isEnabled True if is enabled, false if not.

  void SetVSync(bool isEnabled) override;

  /// \fn bool WindowsWindow::IsVSync() const override;
  ///
  /// \brief Query if this object is v synchronise.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns True if v synchronise, false if not.

  bool IsVSync() const override;

 private:
  /// \fn void WindowsWindow::Initialize(const WindowProps& props);
  ///
  /// \brief Initializes this object.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param props The properties.

  void Initialize(const WindowProps& props);

  /// \fn void WindowsWindow::Shutdown();
  ///
  /// \brief Shuts down this object and frees any resources it is using.
  ///
  /// \author Georg
  /// \date 07/10/2019

  void Shutdown();

  /// \brief The window handle (pointer to GLFWwindow).
  GLFWwindow* m_Window;

  /// \struct WindowData
  ///
  /// \brief Custom/User-defined window data that gets passed to the Window
  /// handling library Used to have less memory transfer, no need to pass an
  /// enitre WindowsWindow class.
  ///
  /// \author Georg
  /// \date 07/10/2019

  struct WindowData {
    /// \brief The title
    std::string Title{"Dwarfworks Engine"};
    /// \brief The width
    unsigned int Width{1280};
    /// \brief The height
    unsigned int Height{720};
    /// \brief True to synchronise
    bool VSync{false};
    // construct appropirate callback for the event
    EventCallbackFn EventCallback;
  };

  /// \brief The window data.
  WindowData m_Data;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_WINDOWS_WINDOW_H_
