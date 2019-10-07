#include "dwpch.h"

#include "Application.h"

namespace Dwarfworks {

Application::Application()
    : m_Window(std::unique_ptr<Window>(Window::Create())) {}

Application::~Application() {}

void Application::Run() {
  // the main loop
  while (IsRunning()) {
    // m_Window->OnUpdate();
  }
}

}  // namespace Dwarfworks
