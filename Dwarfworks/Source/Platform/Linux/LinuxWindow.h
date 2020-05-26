#ifndef PLATFORM_WINDOWS_LINUX_WINDOW_H_
#define PLATFORM_WINDOWS_LINUX_WINDOW_H_

#include "Dwarfworks/Core/Window/Window.h"

#include "Dwarfworks/Graphics/GraphicsContext.h"

#include <GLFW/glfw3.h>
// struct GLFWwindow;

namespace Dwarfworks {

class DW_API LinuxWindow : public Window {
 public:

  explicit LinuxWindow(const WindowProps& props);
  virtual ~LinuxWindow() override;

  void OnUpdate() override;

  unsigned int GetWidth() const override { return m_Data.Width; }
  unsigned int GetHeight() const override { return m_Data.Height; }

  // Window attributes
  void SetEventCallback(const EventCallbackFn& callback) override;

  void SetVSync(bool isEnabled) override;
  bool IsVSync() const override;

  inline void* GetNativeWindow() const override { return m_Window; }

 private:
  void Initialize(const WindowProps& props);
  void Shutdown();

  GLFWwindow* m_Window;
  GraphicsContext* m_Context;

  struct WindowData {
    std::string Title{"Dwarfworks Engine"};
    unsigned int Width{1280};
    unsigned int Height{720};
    bool VSync{false};
    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};

}  // namespace Dwarfworks

#endif  // PLATFORM_WINDOWS_LINUX_WINDOW_H_
