#ifndef CORE_ENTRY_POINT_H_
#define CORE_ENTRY_POINT_H_

// #ifdef DW_PLATFORM_WINDOWS

extern Dwarfworks::Scope<Dwarfworks::Application>
Dwarfworks::CreateApplication();

/// \fn auto main() -> void
///
/// \brief Main entry-point for an application.
///
/// \author Georg
/// \date 07/10/2019

auto main() -> int {
  // TODO: Create Dwarfworks::System to handle system init/shut via RAII
  Dwarfworks::Log::Initialize();

  auto app = Dwarfworks::CreateApplication();
  app->Run();

  return 0;
}

// #endif

#endif  // CORE_ENTRY_POINT_H_
