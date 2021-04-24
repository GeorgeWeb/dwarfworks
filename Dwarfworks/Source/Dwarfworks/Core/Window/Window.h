#ifndef CORE_WINDOW_WINDOW_H_
#define CORE_WINDOW_WINDOW_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Events/EventManager.h"
#include "dwpch.h"

namespace Dwarfworks
{
struct ENGINE_API WindowProps
{
    std::string  Title;
    unsigned int Width;
    unsigned int Height;

    explicit WindowProps(const std::string& title = "Dwarfworks Engine", unsigned int width = 1280,
                         unsigned int height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

// Interface representing a desktop system based window.
// Implemented per platform

class ENGINE_API Window
{
  public:
    // The event callback function.
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const  = 0;
    virtual unsigned int GetHeight() const = 0;

    // Window attributes

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

    virtual void SetVSync(bool isEnabled) = 0;
    virtual bool IsVSync() const          = 0;

    // Get the native window for the platform
    // Note: Currently we're using GLFWwindow for all GLFW supported platforms
    // until implemented using the native APIs
    virtual void* GetNativeWindow() const = 0;

    static Scope<Window> Create(const WindowProps& props = WindowProps {});
};

} // namespace Dwarfworks

#endif // CORE_WINDOW_WINDOW_H_
