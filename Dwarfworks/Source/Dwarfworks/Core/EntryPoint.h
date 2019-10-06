#ifndef CORE_ENTRY_POINT_H_
#define CORE_ENTRY_POINT_H_

#ifdef DW_PLATFORM_WINDOWS

extern Dwarfworks::Application* Dwarfworks::CreateApplication();

int main(int argc, char** argv) {
  Dwarfworks::Log::Initialize();

  DW_CORE_WARN("Initialized Log!");
  auto msg = "folks";
  DW_INFO("Hello {0}.", msg);

  auto app = Dwarfworks::CreateApplication();
  app->Run();
  delete app;
  return 0;
}

#endif

#endif  // CORE_ENTRY_POINT_H_
