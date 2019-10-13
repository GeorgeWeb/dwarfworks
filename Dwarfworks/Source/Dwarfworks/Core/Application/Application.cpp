#include "dwpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Dwarfworks/Core/Input/Input.h"

#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() {
  // set the Single Instance to point to this class only
  s_Instance = this;

  // Create the Application Window
  auto window = Window::Create();
  m_Window.reset(std::move(window));
  // Set the Window event handling for this Application
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));

  // Create (this) Application-centric DebugUI Layer
  m_DebugUILayer = CreateRef<DebugUILayer>();
  PushOverlay(m_DebugUILayer.get());
}

void Application::Run() {
  while (IsRunning()) {
    // Test OpenGL clear color buffer
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Update layers from the LayerStack
    for (auto layer : m_LayerStack) {
      layer->OnUpdate();
    }

    // Render DebugUI Layer
    m_DebugUILayer->Begin();
    for (auto layer : m_LayerStack) {
      layer->OnDebugUIRender();
    }
    m_DebugUILayer->End();

    // Update Window
    m_Window->OnUpdate();
  }
}

void Application::OnEvent(Event& event) {
  // listen for upcoming events and register them
  EventManager eventManager(event);
  // dispatch the event and call its function if it matches the registered event
  eventManager.Dispatch<WindowCloseEvent>(
      DW_BIND_EVENT_FN(Application::OnWindowClosed));

  // call events in reverse order from most top to most bottom layer
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](Layer* layer) {
    layer->OnEvent(event);
    if (event.IsHandled) return;
  });
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClosed(WindowCloseEvent& event) {
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
