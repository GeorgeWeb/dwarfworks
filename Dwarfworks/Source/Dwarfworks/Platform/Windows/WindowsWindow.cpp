#include "dwpch.h"

#include "WindowsWindow.h"

namespace Dwarfworks {

Window* Window::Create(const WindowProps& props) {
  return new WindowsWindow{props};
}

WindowsWindow::WindowsWindow(const WindowProps& props) { Initialize(props); }

WindowsWindow::~WindowsWindow() = default;

void WindowsWindow::OnUpdate() {}

void WindowsWindow::SetEventCallback(const EventCallbackFn& callback) {}

void WindowsWindow::SetVSync(bool isEnabled) {}

bool WindowsWindow::IsVSync() const { return false; }

void WindowsWindow::Initialize(const WindowProps& props) {}

void WindowsWindow::Shutdown(const WindowProps& props) {}

}  // namespace Dwarfworks
