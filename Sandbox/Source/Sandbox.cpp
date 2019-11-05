#include "Sandbox.h"

Sandbox::Sandbox() : Application(), m_Playground(new Playground) {
  PushLayer(m_Playground);
  DW_INFO("Added {0} layer", m_Playground->GetName());
}

Sandbox::~Sandbox() {}

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication() {
  return Dwarfworks::CreateScope<Sandbox>();
}
