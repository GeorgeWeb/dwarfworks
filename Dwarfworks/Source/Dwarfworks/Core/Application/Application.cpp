#include "dwpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Dwarfworks/Core/Input/Input.h"

#include "Dwarfworks/Math/Math.h"

#include "Tests/Test.h"

#include "Dwarfworks/Core/Threading/TaskGenerator.h"

namespace Dwarfworks {

std::atomic<Application*> Application::s_Instance = nullptr;
std::mutex Application::s_Mutex;

Application::Application() {
  // set the Single Instance to point to this class only
  s_Instance = this;

  // Create the Application Window
  auto window = Window::Create();
  m_Window.reset(std::move(window));
  // Set the Window event handling for this Application
  m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));

  // Create Application DebugUI Layer
  m_DebugUILayer = CreateRef<DebugUILayer>();
  PushOverlay(m_DebugUILayer.get());
}

void Application::Run() {
  // Setup Test Menu
  // TODO: Implement the following tests:
  // Tests::TestClearColor* clearColorTest; // Done
  // Tests::TestDebugUIControls* debugUIControlsTest;
  // Tests::TestThreadManager* threadManagerTest;
  Tests::Test* currentTest = nullptr;
  Tests::TestMenu* testMenu = new Tests::TestMenu(currentTest);
  currentTest = testMenu;
  m_LayerStack.PushLayer(currentTest);

  // Register Tests
  testMenu->RegisterTest<Tests::BasicTest>("Basic Test");
  testMenu->RegisterTest<Tests::ClearColorTest>("OpenGL Clear Color Test");

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

  // the main loop
  while (IsRunning()) {
    // Test OpenGL clear color buffer
    glClearColor(1, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    taskGenerator.CreateTasks();

    // Update layers
    for (auto appLayer : m_LayerStack) {
      if (currentTest) {
        currentTest->OnUpdate();
      } else {
        if (appLayer != currentTest) {
          appLayer->OnUpdate();
        }
      }
    }

    // Render layers
    for (auto appLayer : m_LayerStack) {
      if (currentTest) {
        currentTest->OnRender();
      } else {
        if (appLayer != currentTest) {
          appLayer->OnRender();
        }
      }
    }

    // Render DebugUI Layer
    m_DebugUILayer->Begin();
    if (currentTest) {
      if (currentTest != testMenu && ImGui::Button("< Back")) {
        delete currentTest;
        currentTest = testMenu;
      }
      currentTest->OnDebugUIRender();
    } else {
      for (auto appLayer : m_LayerStack) {
        if (appLayer != currentTest) {
          appLayer->OnDebugUIRender();
        }
      }
    }
    m_DebugUILayer->End();

    // TODO: Graphics Rendering
    // Note: When Renderer is implemented

    // Update Window
    m_Window->OnUpdate();
  }

  // cleanup tests
  delete testMenu;

  threadManager.PauseThreads();
  threadManager.JoinThreads();
}

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
  m_IsRunning = false;
  return true;
}

}  // namespace Dwarfworks
