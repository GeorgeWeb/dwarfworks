#ifndef PLATFORM_MAC_MAC_WINDOW_H
#define PLATFORM_MAC_MAC_WINDOW_H

#include "Dwarfworks/Core/Window/Window.h"
#include "Dwarfworks/Renderer/GraphicsContext.h"

#if __clang__
    #include <experimental/propagate_const>
#endif

// Temp.
struct GLFWwindow;

namespace Dwarfworks
{
class ENGINE_API MacWindow final : public Window
{
    struct MacWindowImpl;

  public:
    // TODO: Rename WindowProps to WindowInfo!
    explicit MacWindow(const WindowProps& props);
    ~MacWindow();

    void* Get() const override;
    void* GetNative() const override;

    void OnUpdate() override;

    uint32_t GetWidth() const override;
    uint32_t GetHeight() const override;

    void SetVSyncEnabled(bool enable = false) override;
    bool IsVSyncEnabled() const override;

#if __clang__
    const MacWindowImpl* Pimpl() const { return m_Pimpl.get(); }
#endif
    MacWindowImpl* Pimpl() { return m_Pimpl.get(); }

    void SetEventCallback(const EventCallbackFn& callback) override;

  private:
    void Initialize(const WindowProps& props);
    void Shutdown();

    // cross-platform window handle (Temp. GLFW)
    GLFWwindow*      m_Window;
    GraphicsContext* m_Context;

    WindowState m_Data;

// native extended implementation
// currently only clang implements std::experimental::propagate_const
#if __clang__
    std::experimental::propagate_const<Scope<MacWindowImpl>> m_Pimpl;
#else
    Scope<MacWindowImpl> m_Pimpl;
#endif
};
} // namespace Dwarfworks

#endif // PLATFORM_MAC_MAC_WINDOW_H
