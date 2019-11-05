#include "Sandbox.h"

Sandbox::Sandbox() : Application(), m_Playground(new Playground) {
  PushLayer(m_Playground);
  DW_INFO("Added {0} layer", m_Playground->GetName());
}

Sandbox::~Sandbox() {}

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication() {
  Dwarfworks::RendererAPI::SetAPI(RendererAPI::API::OpenGL);
  return Dwarfworks::CreateScope<Sandbox>();
}
