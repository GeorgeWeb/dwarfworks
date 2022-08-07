#ifndef CORE_APPLICATION_APPLICATION_H
#define CORE_APPLICATION_APPLICATION_H

#include "Dwarfworks/Core/Core.h"

// Window
#include "Dwarfworks/Core/Window/Window.h"

// Layers
#include "Dwarfworks/Core/Layer/LayerStack.h"
#include "Dwarfworks/DebugUI/DebugUILayer.h"

// Events
#include "Dwarfworks/Event/ApplicationEvent.h"

namespace Dwarfworks
{
class ENGINE_API Application : protected Noncopyable
{
  public:
    // Application can only be instantiated with WindowProps.
    Application(const WindowProps& props = WindowProps());

    virtual ~Application(); // Application Teardown

    // Gets the Application singleton instance
    // TODO(georgi): rename Get -> Instance...
    static Application& Get();

    // Executes the event action
    virtual void OnEvent(Event& event);

    // The application/game loop
    void GameLoop();

    float GetLastFrameTime() const { return m_LastFrameTime; }

    void Quit();
    void Minimize();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    // Gets the window for the user's platform
    const Window& GetWindow() const { return *m_Window.get(); }

    bool IsRunning() const { return m_IsRunning; }
    bool IsMinimized() const { return m_IsMinimized; }

  protected:
    // Executes the window closed action
    // True if it succeeds, false if it fails.
    virtual bool OnWindowClosed(WindowCloseEvent& event);
    virtual bool OnWindowResize(WindowResizeEvent& event);

    Scope<Window>     m_Window;
    Ref<DebugUILayer> m_DebugUILayer;
    LayerStack        m_LayerStack;

  private:
    void SetRunning(bool running) { m_IsRunning = running; }
    void SetMinimized(bool minimize) { m_IsMinimized = minimize; }

    bool m_IsRunning {true};
    bool m_IsMinimized {false};

    // Time step
    float m_LastFrameTime {0.0f};

    static Application*   s_Instance;
    static std::once_flag s_instantiateApplicationFlag;
};

Dwarfworks::Scope<Dwarfworks::Application> CreateApplication();

} // namespace Dwarfworks

#endif // CORE_APPLICATION_APPLICATION_H
