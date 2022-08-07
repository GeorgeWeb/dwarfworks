#include "Sandbox.h"

// Application entry point - the main() function
#include "Dwarfworks/Core/EntryPoint.h"

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication()
{
    // Create the Application
    return Dwarfworks::CreateScope<Sandbox>();
}

using namespace Dwarfworks;

static WindowProps props("Dwarfworks Engine", s_ScreenWidth, s_ScreenHeight);

Sandbox::Sandbox() : Application(props)
{
    // Attach the layers to the application
    PushLayer(new SandboxLayer());
}

Sandbox::~Sandbox()
{
    DW_INFO("Sandbox Teardown");
}

void Sandbox::OnEvent(Event& event)
{
    // Base class callbacks.
    Sandbox::OnEvent(event);
}
