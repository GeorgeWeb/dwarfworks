#include "dwpch.h"

#include "WindowsWindow.h"

namespace Dwarfworks {

static bool s_IsGLFWInitialized{false};

Window* Window::Create(const WindowProps& props) {
  return new WindowsWindow{props};
}

WindowsWindow::WindowsWindow(const WindowProps& props) { Initialize(props); }

WindowsWindow::~WindowsWindow() { Shutdown(); };

void WindowsWindow::OnUpdate() {}

void WindowsWindow::SetEventCallback(const EventCallbackFn& callback) {}

void WindowsWindow::SetVSync(bool isEnabled) {
  // set the interval synchronisation time for a frame to be
  // called for rendering depending on v-sync being enabled
  const auto interval = isEnabled ? 1 : 0;  // 1 is default, could be changed
  glfwSwapInterval(interval);
  m_Data.VSync = isEnabled;
}

bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

void WindowsWindow::Initialize(const WindowProps& props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  DW_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width,
               props.Height);

  if (!s_IsGLFWInitialized) {
    // TODO: glfwTerminate() on system shutdown (not on window close!)
    auto success = glfwInit();
    DW_CORE_ASSERT(success, "Could not initialize GLFW!");

    s_IsGLFWInitialized = true;
  }

  // create the window
  m_Window = glfwCreateWindow(static_cast<int>(props.Width),
                              static_cast<int>(props.Height),
                              m_Data.Title.c_str(), nullptr, nullptr);

  // set the current context to the created window
  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);  // v-sync is on by default
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(m_Window); }

}  // namespace Dwarfworks
