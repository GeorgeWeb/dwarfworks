#include "dwpch.h"

#include "Application.h"

namespace Dwarfworks {

Application::Application()
    : m_Window(std::unique_ptr<Window>(Window::Create())) {
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::Run() {
  // the main loop
  while (IsRunning()) {
    m_Window->OnUpdate();
  }
}

void Application::OnEvent(Event& event) {
  EventManager manager(event);

  manager.Dispatch<WindowCloseEvent>(
      DW_BIND_EVENT_FN(Application::OnWindowClosed));

  DW_CORE_INFO("{0}", event);
}

bool Application::OnWindowClosed(WindowCloseEvent& event) {
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
