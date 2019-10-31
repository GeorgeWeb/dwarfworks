// begin PCH
#include "dwpch.h"
// end PCH

#include "Application.h"
#include "Dwarfworks/Math/Math.h"

#ifdef ENABLE_VISUAL_TESTING
#include "Tests/OpenGLClearColorTest.h"
#include "Tests/OpenGLInfoTest.h"
#include "Tests/OpenGLRenderTriangleTest.h"
#include "Tests/ShaderManagerTest.h"
#include "Tests/TestMenu.h"
#endif

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() {
  DW_CORE_ASSERT(!s_Instance, "Instance of Application already exists!");
  // set the single instance to point to the existing application
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
  INIT_TEST_MENU(m_TestMenu, m_CurrentTest);
  // Register Tests
  REGISTER_TEST(Tests::OpenGLInfoTest, "OpenGL Info", m_TestMenu);
  REGISTER_TEST(Tests::OpenGLClearColorTest, "OpenGL Clear Color", m_TestMenu);
  REGISTER_TEST(Tests::OpenGLRenderTriangleTest, "Render Triangle", m_TestMenu);
  REGISTER_TEST(Tests::ShaderManagerTest, "Shader manager", m_TestMenu);
  // Set Current Test Layer to Test Menu
  m_CurrentTest = m_TestMenu.get();
  m_LayerStack.PushLayer(m_CurrentTest);
#endif
}

#ifdef ENABLE_VISUAL_TESTING
Application::~Application() = default;  // TODO: cleanup
#else
Application::~Application() = default;
#endif

void Application::Run() {
  // the main loop
  while (IsRunning()) {
    // fixed update layers
    for (auto appLayer : m_LayerStack) {
      appLayer->OnFixedUpdate();
    }

    // update layers
    for (auto appLayer : m_LayerStack) {
      appLayer->OnUpdate();
    }

    // late update layers
    for (auto appLayer : m_LayerStack) {
      appLayer->OnLateUpdate();
    }

    // render layers
#ifdef ENABLE_VISUAL_TESTING
    // jump into the test layer and hide app layers
    if (m_CurrentTest) {
      m_CurrentTest->OnRender();
    }
    // back in test menu (where all app layers are visible)
    if (m_CurrentTest == m_TestMenu.get()) {
      for (auto appLayer : m_LayerStack) {
        if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
          appLayer->OnRender();
        }
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnRender();
    }
#endif

    // render DebugUI layer
    m_DebugUILayer->Begin();
#ifdef ENABLE_VISUAL_TESTING
    // jump into the test layer and hide app layers
    if (m_CurrentTest) {
      if (m_CurrentTest != m_TestMenu.get() && ImGui::Button("<< Back")) {
        delete m_CurrentTest;
        m_CurrentTest = m_TestMenu.get();
      }
      m_CurrentTest->OnDebugUIRender();
    }
    // back in test menu (where all app layers are visible)
    if (m_CurrentTest == m_TestMenu.get()) {
      for (auto appLayer : m_LayerStack) {
        if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
          appLayer->OnDebugUIRender();
        }
      }
    }
#else
    for (auto appLayer : m_LayerStack) {
      appLayer->OnDebugUIRender();
    }
#endif
    m_DebugUILayer->End();

    // update window (events polling)
    m_Window->OnUpdate();
  }
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
    // TODO: Describe!
    m_LayerStack.PopLayer(m_CurrentTest);
    // TODO: Describe!
    if (m_CurrentTest != m_TestMenu.get()) {
      delete m_CurrentTest;
    }
    m_CurrentTest = nullptr;
    // TODO: Describe!
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
