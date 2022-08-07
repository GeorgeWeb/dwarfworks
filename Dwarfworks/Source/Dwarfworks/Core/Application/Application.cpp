// begin PCH
#include "Dwarfworks/Core/Log/Log.h"
#include "Dwarfworks/Renderer/RenderCommand.h"
#include "dwpch.h"
// end PCH

#include "Application.h"
#include "Dwarfworks/Core/Timestep.h"
#include "Dwarfworks/Renderer/Renderer.h"
#include "Dwarfworks/Renderer/2D/Renderer2D.h"
#include "Dwarfworks/Math/Math.h"

#include "Dwarfworks/Core/Input/KeyCodeDefinitions.h"

// imgui
#include "imgui.h"

// TEMPORARY!
#include "GLFW/glfw3.h"

using namespace Dwarfworks;

Application*   Application::s_Instance;
std::once_flag Application::s_instantiateApplicationFlag;

Application& Application::Get()
{
    std::call_once(s_instantiateApplicationFlag, []() {
        if (!s_Instance)
        {
            s_Instance = new Application();
        }
    });
    return *s_Instance;
}

// Application::Application()

Application::Application(const WindowProps& props)
{
    DW_CORE_ASSERT(!s_Instance, "Can have only one Application instance!");
    s_Instance = this;
    // Create the Application Window
    m_Window = Window::Create(props);
    // Set the Window event handling for this Application
    m_Window->SetEventCallback(BIND_MEMBER(Application::OnEvent));

    // Initialize the Renderer
    Renderer::Initialize();

    // Create Application DebugUI Layer (as overlay)
    m_DebugUILayer = CreateRef<DebugUILayer>();
    PushOverlay(m_DebugUILayer.get());
}

Application::~Application()
{
    // Cleanup DebugUI overlay resources
    m_LayerStack.PopOverlay(m_DebugUILayer.get());
    // Renderer::Shutdown();
    DW_CORE_INFO("Closed the Application!");
}

void Application::GameLoop()
{
    while (m_IsRunning)
    {
        // -------------------------------- //
        // -- Timestep calculation -------- //
        // -------------------------------- //

        float    time      = static_cast<float>(glfwGetTime()); // TODO:Platform::GetTime()
        Timestep deltaTime = time - m_LastFrameTime;
        m_LastFrameTime    = time;

        if (!m_IsMinimized)
        {
            // -------------------------------- //
            // -- Update layers --------------- //
            // -------------------------------- //
            for (auto layer : m_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }

            // -------------------------------- //
            // -- Render layers --------------- //
            // -------------------------------- //
            for (auto layer : m_LayerStack)
            {
                layer->OnRender();
            }

            // -------------------------------- //
            // -- Render DebugUI overlay ------ //
            // -------------------------------- //
            m_DebugUILayer->Begin();
            for (auto layer : m_LayerStack)
            {
                layer->OnDebugUIRender();
            }
            m_DebugUILayer->End();
        }

        // -------------------------------- //
        // -- Poll window events ---------- //
        // -------------------------------- //

        // TODO: If minimized - don't swap buffers
        // if (!m_IsMinimized)
        {
            m_Window->OnUpdate();
        }
    }
}

void Application::OnEvent(Event& event)
{
    // listen for upcoming events and register them
    EventDispatcher eventDispatcher(event);
    // dispatch the event and call its function if it matches the registered event
    eventDispatcher.Dispatch<WindowCloseEvent>(BIND_MEMBER(Application::OnWindowClosed));
    // Note: Default resizing behaviour, refactor later.
    eventDispatcher.Dispatch<WindowResizeEvent>(BIND_MEMBER(Application::OnWindowResize));

    // call events in reverse order from most top to most bottom layer
    std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto&& layer) {
        layer->OnEvent(event);
        // exit when the event is handled
        if (event.IsHandled())
        {
            DW_CORE_WARN("Handled event {}", event.GetName());
            return;
        }
    });
}

void Application::Quit()
{
    SetRunning(false);
}

void Application::Minimize()
{
    SetMinimized(true);
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack.PushOverlay(layer);
}

bool Application::OnWindowClosed(WindowCloseEvent& event)
{
    // stop running
    SetRunning(false);

    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& event)
{
    if (event.GetWidth() == 0 || event.GetHeight() == 0)
    {
        SetMinimized(true);
    }

    SetMinimized(false);
    Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

    return false;
}
