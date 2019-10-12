#include "dwpch.h"

#include "Application.h"

#include <glad/glad.h>

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() {
  s_Instance = this;

  // m_Window = CreateScope<Window>(Window::Create());
  // m_Window = Window::Create();
  auto window = Window::Create();
  m_Window.reset(std::move(window));
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));
}

void Application::Run() {
  // helper lambda for update a layer
  const auto updateLayer = [](Layer* layer) { layer->OnUpdate(); };

  // the main loop
  while (IsRunning()) {
    glClearColor(1, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    std::for_each(m_LayerStack.begin(), m_LayerStack.end(), updateLayer);
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

void Application::PushLayer(Layer* layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
  m_LayerStack.PushOverlay(layer);
  layer->OnAttach();
}

bool Application::OnWindowClosed(WindowCloseEvent& event) {
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
