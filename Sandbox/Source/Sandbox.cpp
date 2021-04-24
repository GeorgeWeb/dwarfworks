#include "Sandbox.h"

// generic playground (currently 2D stuff)
#include "SandboxLayer.h"

static Dwarfworks::WindowProps props("Dwarfworks Engine", s_ScreenWidth, s_ScreenHeight);

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication()
{
    // Default RendererAPI::API value is OpenGL
    // Set DirectX 12 as the API to launch with
    Dwarfworks::RendererAPI::SetAPI(RendererAPI::API::OpenGL);

    // Create the Application
    return Dwarfworks::CreateScope<Sandbox>();
}

Sandbox::Sandbox() : Application(props)
{
    // Attach the layers to the application
    PushLayer(new SandboxLayer());
}

// Application entry point - the main() function
#include <Dwarfworks/Core/EntryPoint.h>
