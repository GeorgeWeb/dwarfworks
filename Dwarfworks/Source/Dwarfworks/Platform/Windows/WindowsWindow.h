#ifndef PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
#define PLATFORM_WINDOWS_WINDOWS_WINDOW_H_

#include "../../Core/Window/Window.h"

namespace Dwarfworks {

class DW_API WindowsWindow : public Window {
 public:
  explicit WindowsWindow(const WindowProps& props);
  virtual ~WindowsWindow() = default;

  void OnUpdate() override;

  unsigned int GetWidth() const override { return m_Data.Width; }
  unsigned int GetHeight() const override { return m_Data.Height; }

  // Window attributes
  void SetEventCallback(const EventCallbackFn& callback) override;
  void SetVSync(bool isEnabled) override;
  bool IsVSync() const override;

 private:
  // "Virtuality" separation of init/shut logic for derived classes
  // Example extensions: UniversalWindowsApp(UWP) Window or WindowsPhone Window
  virtual void Initialize(const WindowProps& props);
  virtual void Shutdown(const WindowProps& props);

  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;
    // construct appropirate callback for the event
    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
