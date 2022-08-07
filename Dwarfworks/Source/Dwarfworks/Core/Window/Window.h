#ifndef CORE_WINDOW_WINDOW_H
#define CORE_WINDOW_WINDOW_H

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Event/EventDispatcher.h"

namespace Dwarfworks
{
/**
 * @brief
 *
 */
struct ENGINE_API WindowProps
{
    std::string Title;
    uint32_t    Width;
    uint32_t    Height;

    explicit WindowProps(const std::string& title = "Dwarfworks Engine", unsigned int width = 1280,
                         unsigned int height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

/**
 * @brief
 *
 */
using EventCallbackFn = std::function<void(Event&)>;

/**
 * @brief Interface representing a desktop system based window.
 *
 */
class ENGINE_API Window
{
  public:
    virtual ~Window() = default;

    // Get the native window for the platform
    virtual void* Get() const       = 0;
    virtual void* GetNative() const = 0;

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const  = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetVSyncEnabled(bool enable = false) = 0;
    virtual bool IsVSyncEnabled() const               = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

    static Scope<Window> Create(const WindowProps& props = WindowProps {});
};

/**
 * @brief
 *
 */
struct WindowState final
{
    EventCallbackFn EventCallback {};

    std::string Title {"Dwarfworks Engine"};
    uint32_t    Width {1280};
    uint32_t    Height {720};
    bool        VSync {false};
};

} // namespace Dwarfworks

#endif // CORE_WINDOW_WINDOW_H
