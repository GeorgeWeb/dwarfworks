#ifndef PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
#define PLATFORM_WINDOWS_WINDOWS_WINDOW_H_

#include "../../Core/Window/Window.h"

namespace Dwarfworks {
namespace Platform {

class DW_API WindowsWindow : public Core::Window {
 public:
  explicit WindowsWindow(const Core::WindowProps& props);
  ~WindowsWindow() = default;

 private:
  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;
    // construct appropirate callback for the event
    EventCallbackFn EventCallback;
  };
};

}  // namespace Platform
}  // namespace Dwarfworks

#endif  // PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
