#ifndef CORE_ENTRY_POINT_H_
#define CORE_ENTRY_POINT_H_

extern Dwarfworks::Application* Dwarfworks::CreateApplication();

auto main() -> int {
  // TODO: Create Dwarfworks::System to handle system init/shut via RAII
  Dwarfworks::Log::Initialize();

  auto app = Dwarfworks::CreateApplication();
  app->GameLoop();
  delete app;

  return 0;
}

#endif  // CORE_ENTRY_POINT_H_
