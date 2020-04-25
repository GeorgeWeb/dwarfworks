// begin PCH
#include "dwpch.h"
// end PCH

#include "Application.h"
#include "Dwarfworks/Core/Timestep.h"
#include "Dwarfworks/Math/Math.h"

// imgui
#include "imgui.h"

#ifdef ENABLE_VISUAL_TESTING
#include "Testing/OpenGLTests/OpenGLClearColorTest.h"
#include "Testing/OpenGLTests/OpenGLInfoTest.h"
#include "Testing/OpenGLTests/OpenGLRenderTriangleTest.h"
#endif

// TEMPORARY!
#include <GLFW/glfw3.h>

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() {
  DW_CORE_ASSERT(!s_Instance, "Instance of Application already exists!");
  // set the single instance to point to the existing application
  s_Instance = this;

  // Create the Application Window
  auto window = Window::Create();
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
  REGISTER_TEST(Testing::OpenGLInfoTest, "OpenGL Info", m_TestMenu);
  REGISTER_TEST(Testing::OpenGLClearColorTest, "OpenGL Clear Color",
                m_TestMenu);
  REGISTER_TEST(Testing::OpenGLRenderTriangleTest, "OpenGL Render Triangle",
                m_TestMenu);
  // Set Current Test Layer to Test Menu
  m_CurrentTest = m_TestMenu.get();
  m_LayerStack.PushLayer(m_CurrentTest);
#endif
}

Application::~Application() {
  // cleanup Test layer resources
  #ifdef ENABLE_VISUAL_TESTING
  if (m_CurrentTest) {
    // TODO: Provide explanation!
    m_LayerStack.PopLayer(m_CurrentTest);
    // TODO: Provide explanation!
    if (m_CurrentTest != m_TestMenu.get()) {
      delete m_CurrentTest;
    }
    m_CurrentTest = nullptr;
    // TODO: Provide explanation!
    m_LayerStack.PopLayer(m_TestMenu.get());
  }
  #endif

  // cleanup DebugUI overlay resources
  m_LayerStack.PopOverlay(m_DebugUILayer.get());

  DW_CORE_INFO("Closed the Application!");
}

void Application::GameLoop() {
  while (IsRunning()) {
    // -------------------------------- //
    // -- Timestep calculation -------- //
    // -------------------------------- //

    float time = static_cast<float>(glfwGetTime());  // TODO:Platform::GetTime()
    Timestep deltaTime = time - m_LastFrameTime;
    m_LastFrameTime = time;

    // -------------------------------- //
    // -- Update layers --------------- //
    // -------------------------------- //

    for (auto appLayer : m_LayerStack) {
      appLayer->OnUpdate(deltaTime);
    }

    // -------------------------------- //
    // -- Render layers --------------- //
    // -------------------------------- //

    for (auto appLayer : m_LayerStack) {
      appLayer->OnRender();
    }

    // -------------------------------- //
    // -- Render DebugUI overlay ------ //
    // -------------------------------- //

    m_DebugUILayer->Begin();

    for (auto appLayer : m_LayerStack) {
      appLayer->OnDebugUIRender();
    }

    m_DebugUILayer->End();

    // -------------------------------- //
    // -- Poll window events ---------- //
    // -------------------------------- //

    m_Window->OnUpdate();
  }
}

void Application::DebugGameLoop() {
  #ifdef ENABLE_VISUAL_TESTING
  while (IsRunning()) {
    // -------------------------------- //
    // -- Timestep calculation -------- //
    // -------------------------------- //

    float time = static_cast<float>(glfwGetTime());  // TODO:Platform::GetTime()
    Timestep deltaTime = time - m_LastFrameTime;
    m_LastFrameTime = time;

    // -------------------------------- //
    // -- Update layers --------------- //
    // -------------------------------- //

    for (auto appLayer : m_LayerStack) {
      appLayer->OnUpdate(deltaTime);
    }

    // -------------------------------- //
    // -- Render layers --------------- //
    // -------------------------------- //

    // if the current Test layer is active, render this layer.
    if (m_CurrentTest) {
      m_CurrentTest->OnRender();
    }

    // if the current Test layer is TestMenu, render all the 
    // Application layers excluding the current Test layer.
    if (m_CurrentTest == m_TestMenu.get()) {
      for (auto appLayer : m_LayerStack) {
        if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
          appLayer->OnRender();
        }
      }
    }

    // -------------------------------- //
    // -- Render DebugUI overlay ------ //
    // -------------------------------- //

    m_DebugUILayer->Begin();

    // if the current Test layer is active, render DebugUI for this layer.
    if (m_CurrentTest) {
      // if the current Test layer is not TestMenu, display a BACK button
      // and set it to point to TestMenu upon clicking the BACK button.
      if (m_CurrentTest != m_TestMenu.get() && ImGui::Button("Menu")) {
        delete m_CurrentTest;
        m_CurrentTest = m_TestMenu.get();
      }
      m_CurrentTest->OnDebugUIRender();
    }

    // if the current Test layer is TestMenu, render DebugUI for 
    // all Application layers excluding the current Test layer.
    if (m_CurrentTest == m_TestMenu.get()) {
      for (auto appLayer : m_LayerStack) {
        if (appLayer != m_CurrentTest && appLayer != m_TestMenu.get()) {
          appLayer->OnDebugUIRender();
        }
      }
    }

    m_DebugUILayer->End();

    // -------------------------------- //
    // -- Poll window events ---------- //
    // -------------------------------- //

    m_Window->OnUpdate();
  }
  #endif
}

void Application::OnEvent(Event& event) {
  // listen for upcoming events and register them
  EventManager eventManager(event);
  // dispatch the event and call its function if it matches the registered event
  eventManager.Dispatch<WindowCloseEvent>(
      DW_BIND_EVENT_FN(Application::OnWindowClosed));

  // call events in reverse order from most top to most bottom layer
  std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto layer) {
    layer->OnEvent(event);
    if (event.IsHandled) return;
  });
}


void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* layer) { m_LayerStack.PushOverlay(layer); }

bool Application::OnWindowClosed(WindowCloseEvent& event) {
  // stop running
  SetRunning(false);
  return true; // block
}

}  // namespace Dwarfworks
