#include "dwpch.h"

#include "WindowsWindow.h"

#include "../../Core/Events/ApplicationEvent.h"
#include "../../Core/Events/KeyEvent.h"
#include "../../Core/Events/MouseEvent.h"

// Glad
#include <glad/glad.h>
// glfw
#include <GLFW/glfw3.h>

namespace Dwarfworks {

static bool s_IsGLFWInitialized{false};

Window* Window::Create(const WindowProps& props) {
  return new WindowsWindow{props};
}

WindowsWindow::WindowsWindow(const WindowProps& props) { Initialize(props); }

WindowsWindow::~WindowsWindow() { Shutdown(); };

void WindowsWindow::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void WindowsWindow::SetEventCallback(const EventCallbackFn& callback) {
  m_Data.EventCallback = callback;
}

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
    // temporary until abstracted away in a GLFWErrorCallback function
    glfwSetErrorCallback([](int error, const char* description) {
      DW_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    });
    s_IsGLFWInitialized = true;
  }

  // create the window
  m_Window = glfwCreateWindow(static_cast<int>(props.Width),
                              static_cast<int>(props.Height),
                              m_Data.Title.c_str(), nullptr, nullptr);

  // set the current context to the created window
  glfwMakeContextCurrent(m_Window);

  // load OpenGL through the Glad GL Loader
  auto status =
      gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  DW_CORE_ASSERT(status, "Failed to initialize Glad!");

  // set the custom window data to the GLFWwindow
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);  // v-sync is on by default

  // ------------------
  // set glfw callbacks
  // ------------------

  // window resize
  glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width,
                                         int height) {
    auto& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
    auto event = WindowResizeEvent(width, height);
    // update the window dimensions
    data.Width = width;
    data.Height = height;
    // set the window resize callback
    data.EventCallback(event);
  });

  // window close
  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
    auto& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
    auto event = WindowCloseEvent{};
    // set the window close callback
    data.EventCallback(event);
  });

  // key action
  glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mods) {
    auto& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

    switch (action) {
      case GLFW_PRESS: {
        auto event = KeyPressedEvent(key, 0);
        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        auto event = KeyReleasedEvent(key);
        data.EventCallback(event);
        break;
      }
      case GLFW_REPEAT: {
        // temporarily set to 1, but should consider extracting the exact number
        // of repeats in future iteration of this function
        auto event = KeyPressedEvent(key, 1);
        data.EventCallback(event);
        break;
      }
    }
  });

  // mouse button action
  glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button,
                                          int action, int mods) {
    auto& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

    switch (action) {
      case GLFW_PRESS: {
        auto event = MouseButtonPressedEvent(button);
        data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE: {
        auto event = MouseButtonReleasedEvent(button);
        data.EventCallback(event);
        break;
      }
    }
  });

  // mouse scroll action
  glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset,
                                     double yOffset) {
    auto& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

    const auto xOffsetFloat = static_cast<float>(xOffset);
    const auto yOffsetFloat = static_cast<float>(yOffset);
    auto event = MouseScrolledEvent(xOffsetFloat, yOffsetFloat);
    data.EventCallback(event);
  });

  // mouse cursor move action
  glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos,
                                        double yPos) {
    auto& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

    const auto xPosFloat = static_cast<float>(xPos);
    const auto yPosFloat = static_cast<float>(yPos);
    auto event = MouseMovedEvent(xPosFloat, yPosFloat);
    data.EventCallback(event);
  });
}

void WindowsWindow::Shutdown() { glfwDestroyWindow(m_Window); }

}  // namespace Dwarfworks
