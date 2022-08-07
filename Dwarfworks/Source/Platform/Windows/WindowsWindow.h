#ifndef PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
#define PLATFORM_WINDOWS_WINDOWS_WINDOW_H_

#include "Dwarfworks/Core/Window/Window.h"
#include "Dwarfworks/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dwarfworks
{
class ENGINE_API WindowsWindow final : public Window
{
  public:
    explicit WindowsWindow(const WindowProps& props);
    ~WindowsWindow();

    void* Get() const override;
    void* GetNative() const override;

    void OnUpdate() override;

    uint32_t GetWidth() const override { return m_Data.Width; }
    uint32_t GetHeight() const override { return m_Data.Height; }

    void SetVSyncEnabled(bool enable = false) override;
    bool IsVSyncEnabled() const override;

    void SetEventCallback(const EventCallbackFn& callback) override;

  private:
    void Initialize(const WindowProps& props);
    void Shutdown();

    /// The native window handle
    GLFWwindow*      m_Window;
    GraphicsContext* m_Context;

    WindowState m_Data;
};

} // namespace Dwarfworks

#endif // PLATFORM_WINDOWS_WINDOWS_WINDOW_H_
