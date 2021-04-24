// begin PCH
#include "dwpch.h"
// end PCH

#include "Application.h"
#include "Dwarfworks/Core/Timestep.h"
#include "Dwarfworks/Graphics/Renderer.h"
#include "Dwarfworks/Math/Math.h"

// imgui
#include "imgui.h"

// TEMPORARY!
#include <GLFW/glfw3.h>

namespace Dwarfworks
{
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

Application::Application(const WindowProps& props)
{
    DW_CORE_ASSERT(!s_Instance, "Can have only one Application instance!");
    s_Instance = this;
    // Create the Application Window
    m_Window = Window::Create(props);
    // Set the Window event handling for this Application
    m_Window->SetEventCallback(DW_BIND_EVENT_FN(Application::OnEvent));

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
    DW_CORE_INFO("Closed the Application!");
}

void Application::GameLoop()
{
    while (IsRunning())
    {
        // -------------------------------- //
        // -- Timestep calculation -------- //
        // -------------------------------- //

        float    time      = static_cast<float>(glfwGetTime()); // TODO:Platform::GetTime()
        Timestep deltaTime = time - m_LastFrameTime;
        m_LastFrameTime    = time;

        if (!IsMinimized())
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

            // TODO: If minimized - don't swap buffers
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
        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    // listen for upcoming events and register them
    EventManager eventManager(event);
    // dispatch the event and call its function if it matches the registered event
    eventManager.Dispatch<WindowCloseEvent>(DW_BIND_EVENT_FN(Application::OnWindowClosed));
    // Note: Default resizing behaviour, refactor later.
    eventManager.Dispatch<WindowResizeEvent>(DW_BIND_EVENT_FN(Application::OnWindowResize));

    // call events in reverse order from most top to most bottom layer
    std::for_each(m_LayerStack.rbegin(), m_LayerStack.rend(), [&](auto layer) {
        layer->OnEvent(event);
        if (event.IsHandled)
            return;
    });
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
    return true; // block
}

bool Application::OnWindowResize(WindowResizeEvent& event)
{
    if (event.GetWidth() == 0 || event.GetHeight() == 0)
    {
        SetMinimized(true);
        return false;
    }

    SetMinimized(false);
    Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

    return false;
}

} // namespace Dwarfworks
