#include "dwpch.h"

#include "Application.h"

namespace Dwarfworks {

Application::Application()
    : m_Window(std::unique_ptr<Window>(Window::Create())) {
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::Run() {
  // helper lambda for update a layer
  auto updateLayer = [](Layer* layer) { layer->OnUpdate(); };

  // the main loop
  while (IsRunning()) {
    std::for_each(m_LayerStack.begin(), m_LayerStack.end(), updateLayer);
    m_Window->OnUpdate();
  }
}

void Application::OnEvent(Event& event) {
  // listen for upcoming events and register them
  EventManager manager(event);
  // dispatch the event and call its function if it matches the registered event
  manager.Dispatch<WindowCloseEvent>(
      DW_BIND_EVENT_FN(Application::OnWindowClosed));

  DW_CORE_INFO("{0}", event);

  // call events in reverse order from most top to most bottom layer
  auto handleLayerEvent = [&event](Layer* layer) -> void {
    layer->OnEvent(event);
    if (event.IsHandled) {
      return;
    }
  };

  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), handleLayerEvent);
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClosed(WindowCloseEvent& event) {
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
