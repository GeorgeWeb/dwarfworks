#include "Sandbox.h"

// generic playground (currently 2D stuff)
#include "Playground.h"

// Application entry point - the main() function
#include <Dwarfworks/Core/EntryPoint.h>

static Dwarfworks::WindowProps props("Dwarfworks Engine", s_ScreenWidth,
                                     s_ScreenHeight);

Dwarfworks::Application* Dwarfworks::CreateApplication() {
  Dwarfworks::RendererAPI::SetAPI(RendererAPI::API::OpenGL);
  return new Sandbox();
}

Sandbox::Sandbox() : Application(props) {
  // attach the layers to the application
  PushLayer(new Playground);
}
