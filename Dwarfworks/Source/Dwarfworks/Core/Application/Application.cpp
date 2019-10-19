#include "dwpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Dwarfworks/Core/Input/Input.h"

#include "Dwarfworks/Math/Math.h"

/** Disable threading for now
#include "Dwarfworks/Core/Threading/TaskGenerator.h"
*/

#ifdef ENABLE_VISUAL_TESTING
#include "Tests/Test.h"
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
  m_TestMenu = CreateRef<Tests::TestMenu>(m_CurrentTest);
  m_CurrentTest = m_TestMenu.get();
  m_LayerStack.PushLayer(m_CurrentTest);
#endif
}

#ifdef ENABLE_VISUAL_TESTING
Application::~Application() = default;
#else
Application::~Application() = default;
#endif

void Application::Run() {
#ifdef ENABLE_VISUAL_TESTING
  // Register Tests
  m_TestMenu->RegisterTest<Tests::BasicTest>("Basic Test");
  m_TestMenu->RegisterTest<Tests::ClearColorTest>("OpenGL Clear Color Test");
#endif

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
    glClearColor(0.2f, 0.2, 0.2, 1);
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

    // TODO: Graphics Rendering
    // Note: When Renderer is implemented

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
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](Layer* layer) {
    layer->OnEvent(event);
    if (event.IsHandled) return;
  });
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClosed(WindowCloseEvent& event) {
#ifdef ENABLE_VISUAL_TESTING
  // free Test layers
  if (m_CurrentTest) {
    m_LayerStack.PopLayer(m_CurrentTest);
    m_CurrentTest = nullptr;
  }
#endif
  // free DebugUI Overlay
  m_LayerStack.PopOverlay(m_DebugUILayer.get());
  m_DebugUILayer = nullptr;
  // stop running
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
