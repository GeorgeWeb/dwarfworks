#ifndef PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
#define PLATFORM_WINDOWS_WINDOWS_WINDOW_H_

#include "Dwarfworks/Core/Window/Window.h"
#include "Dwarfworks/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Dwarfworks
{
class ENGINE_API WindowsWindow : public Window
{
  public:
    explicit WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow() override;

    void OnUpdate() override;

    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }

    void SetEventCallback(const EventCallbackFn& callback) override;

    void SetVSync(bool isEnabled) override;
    bool IsVSync() const override;

    inline void* GetNativeWindow() const override { return m_Window; }

  private:
    void Initialize(const WindowProps& props);
    void Shutdown();

    /// The native window handle
    GLFWwindow*            m_Window;
    Scope<GraphicsContext> m_Context;

    struct WindowData
    {
        std::string  Title  = "Dwarfworks Engine";
        unsigned int Width  = 1280;
        unsigned int Height = 720;
        bool         VSync  = false;
        // construct appropriate callback for the event
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

} // namespace Dwarfworks

#endif // PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
