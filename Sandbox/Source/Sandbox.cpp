#include "Sandbox.h"

// Application entry point - the main() function
#include <Dwarfworks/Core/EntryPoint.h>

static Dwarfworks::WindowProps props("Dwarfworks Engine", s_ScreenWidth,
                                     s_ScreenHeight);

Dwarfworks::Application* Dwarfworks::CreateApplication() {
  Dwarfworks::RendererAPI::SetAPI(RendererAPI::API::OpenGL);
  return new Sandbox();
}

Sandbox::Sandbox() : Application(props) {
  // GetWindow()->SetProps(props);

  // initialize application layers
  m_Layers.push_back(new Playground);
  m_Layers.push_back(new Basic3D);

  // attach the layers to the application
  for (auto layer : m_Layers) {
    if (layer->IsOverlay()) {
      PushOverlay(layer);
    } else {
      PushLayer(layer);
    }
    // debug print
    std::string layerName = layer->GetName();
    std::string layerType = layer->IsOverlay() ? "overlay" : "layer";
    DW_INFO("Added {0} {1}.", layerName, layerType);
  }
}
