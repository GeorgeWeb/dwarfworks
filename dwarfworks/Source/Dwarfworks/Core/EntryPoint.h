#ifndef DWARFWORKS_CORE_ENTRY_POINT_H_
#define DWARFWORKS_CORE_ENTRY_POINT_H_

#ifdef DWARF_PLATFORM_WINDOWS

extern Dwarfworks::Core::Application* Dwarfworks::Core::CreateApplication();

int main(int argc, char** argv) {
  Dwarfworks::Core::Log::Initialize();

  DWARF_CORE_WARN("Initialized Log!");
  auto msg = "folks";
  DWARF_INFO("Hello {0}.", msg);

  auto app = Dwarfworks::Core::CreateApplication();
  app->Run();
  delete app;
  return 0;
}

#endif  // DWARFWORKS_PLATFORM_WINDOWS

#endif  // DWARFWORKS_CORE_ENTRY_POINT_H_
