#include "dwpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Dwarfworks/Core/Input/Input.h"

#include "Dwarfworks/Math/Math.h"

/** Disable threading for now
#include "Dwarfworks/Core/Threading/TaskGenerator.h"
*/

#ifdef ENABLE_VISUAL_TESTING

#include "Tests/TestMenu.h"
#endif

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() {
  // set the Single Instance to point to this class only
  s_Instance = this;

  // Create the Application Window
  auto window = IWindow::Create();
  m_Window.reset(std::move(window));
  // Set the Window event handling for this Application
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));

  // Create Application DebugUI Layer
  m_DebugUILayer = CreateRef<DebugUILayer>();
  PushOverlay(m_DebugUILayer.get());

#ifdef ENABLE_VISUAL_TESTING
  // Create Test Menu
  m_TestMenu = CreateRef<Tests::TestMenu>(m_CurrentTest);
  // Register Tests
  m_TestMenu->RegisterTest<Tests::OpenGLInfoTest>("OpenGL Info");
  m_TestMenu->RegisterTest<Tests::OpenGLClearColorTest>("OpenGL Clear Color");
  m_TestMenu->RegisterTest<Tests::OpenGLRenderTriangleTest>("Render Triangle");
  // Set Current Test Layer to Test Menu
  m_CurrentTest = m_TestMenu.get();
  m_LayerStack.PushLayer(m_CurrentTest);
#endif
}

#ifdef ENABLE_VISUAL_TESTING
Application::~Application() = default;  // TODO!
#else
Application::~Application() = default;
#endif

void Application::Run() {
  /** Disable threading for now
  ThreadManager threadManager;
  threadManager.CreateTaskLists();
  threadManager.RunThreads();

  TaskGenerator taskGenerator(&threadManager);
  taskGenerator.CreateTasks();
  taskGenerator.CreateTasks();
  taskGenerator.CreateTasks();
  taskGenerator.CreateTasks();

  // threadManager.ThreadProcess();
  threadManager.UnpauseThreads();
  */

  // the main loop
  while (IsRunning()) {
    // Test OpenGL clear color buffer
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /** Disable threading for now
    taskGenerator.CreateTasks();
    */

    // Update layers
#ifdef ENABLE_VISUAL_TESTING
    if (m_CurrentTest) {
      m_CurrentTest->OnUpdate();
    }
    for (auto appLayer : m_LayerStack) {
      if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
        appLayer->OnUpdate();
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnUpdate();
    }
#endif

    // Render layers
#ifdef ENABLE_VISUAL_TESTING
    if (m_CurrentTest) {
      m_CurrentTest->OnRender();
    }
    for (auto appLayer : m_LayerStack) {
      if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
        appLayer->OnRender();
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnRender();
    }
#endif

    // Render DebugUI Layer
    m_DebugUILayer->Begin();
#ifdef ENABLE_VISUAL_TESTING
    if (m_CurrentTest) {
      if (m_CurrentTest != m_TestMenu.get() && ImGui::Button("<< Back")) {
        delete m_CurrentTest;
        m_CurrentTest = m_TestMenu.get();
      }
      m_CurrentTest->OnDebugUIRender();
    }
    for (auto appLayer : m_LayerStack) {
      if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
        appLayer->OnDebugUIRender();
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnDebugUIRender();
    }
#endif
    m_DebugUILayer->End();

    // Update Window
    m_Window->OnUpdate();
  }

  /** Disable threading for now
  threadManager.PauseThreads();
  threadManager.JoinThreads();
  */
}  // namespace Dwarfworks

void Application::OnEvent(Event& event) {
  // listen for upcoming events and register them
  EventManager eventManager(event);
  // dispatch the event and call its function if it matches the registered event
  eventManager.Dispatch<WindowCloseEvent>(
      DW_BIND_EVENT_FN(Application::OnWindowClosed));

  // call events in reverse order from most top to most bottom layer
#ifdef ENABLE_VISUAL_TESTING
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto layer) {
    if (layer != m_CurrentTest && layer != m_TestMenu.get()) {
      layer->OnEvent(event);
      if (event.IsHandled) return;
    }
  });
#else
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto layer) {
    layer->OnEvent(event);
    if (event.IsHandled) return;
  });
#endif
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClosed(WindowCloseEvent& event) {
#ifdef ENABLE_VISUAL_TESTING
  // free Test layers
  if (m_CurrentTest) {
    // ... desc
    m_LayerStack.PopLayer(m_CurrentTest);
    // ... desc
    if (m_CurrentTest != m_TestMenu.get()) {
      delete m_CurrentTest;
    }
    m_CurrentTest = nullptr;
    // ... desc
    m_LayerStack.PopLayer(m_TestMenu.get());
  }
#endif
  // free DebugUI Overlay
  m_LayerStack.PopOverlay(m_DebugUILayer.get());
  // stop running
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
