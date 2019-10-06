#ifndef CORE_WINDOW_WINDOW_H_
#define CORE_WINDOW_WINDOW_H_

#include "dwpch.h"

#include "../Core.h"
#include "../Events/EventDispatcher.h"

namespace Dwarfworks {

struct WindowProps {
  std::string Title;
  unsigned int Width;
  unsigned int Height;

  explicit WindowProps(const std::string& title = "Dwarfworks Engine",
                       unsigned int width = 1280, unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
};

// Interface representing a desktop system based window
// Implemented per platform
class DW_API Window {
 public:
  using EventCallbackFn = std::function<void(Event&)>;

  // CRTP or no CRTP, we need the virtual destructor
  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  // Window attributes
  virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
  virtual void SetVSync(bool isEnabled) = 0;
  virtual bool IsVSync() const = 0;

  // Here just for a remainder for future implementation
  // virtual void* GetNativeWindow() const = 0

  static Window* Create(const WindowProps& props = WindowProps{});
};

}  // namespace Dwarfworks

#endif  // CORE_WINDOW_WINDOW_H_
