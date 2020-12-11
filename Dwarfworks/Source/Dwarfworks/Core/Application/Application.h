#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "Dwarfworks/Core/Core.h"

// Window
#include "Dwarfworks/Core/Window/Window.h"

// Layers
#include "Dwarfworks/Core/Layers/LayerStack.h"
#include "Dwarfworks/DebugUI/DebugUILayer.h"

// Events
#include "Dwarfworks/Events/ApplicationEvent.h"

namespace Dwarfworks {

class DW_API Application {
 public:
  // Application can only be instantiated with WindowProps.
  Application(const WindowProps& props = WindowProps());
  virtual ~Application(); // Application Teardown

  // Disable moving or copying Applications for now
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  // Gets the Application singleton instance
  static Application& Get();

  // The application/game loop
  virtual void GameLoop();

  // Executes the event action
  virtual void OnEvent(Event& event);

  inline float GetLastFrameTime() const noexcept { return m_LastFrameTime; }

  // return the frames per second calculated in the Run loop

  // Pushes a layer
  void PushLayer(Layer* layer);
  // Pushes an overlay
  void PushOverlay(Layer* layer);

  // Gets the window for the user's platform
  inline Window& GetWindow() /*const*/ { return *m_Window; }

 protected:
  // Executes the window closed action
  // True if it succeeds, false if it fails.
  virtual bool OnWindowClosed(WindowCloseEvent& event);
  virtual bool OnWindowResize(WindowResizeEvent& event);

  // Query if the application is running
  inline bool IsRunning() const { return m_Running; }
  // Set the application running state
  inline void SetRunning(bool running) { m_Running = running; }

  inline bool IsMinimized() const { return m_Minimized; }
  inline void SetMinimized(bool minimized) { m_Minimized = minimized; }

 protected:
  Scope<Window> m_Window;
  Ref<DebugUILayer> m_DebugUILayer;
  LayerStack m_LayerStack;

 private:
  bool m_Running = true;
  bool m_Minimized = false;

  // Time step
  float m_LastFrameTime = 0.0f;

private:
  static Application* s_Instance;
  static std::once_flag s_instantiateApplicationFlag;
};

Dwarfworks::Application* CreateApplication();

}  // namespace Dwarfworks

#endif  // CORE_APPLICATION_APPLICATION_H_
