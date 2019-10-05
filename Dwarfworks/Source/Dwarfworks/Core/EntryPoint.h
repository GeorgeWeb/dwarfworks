#ifndef CORE_ENTRY_POINT_H_
#define CORE_ENTRY_POINT_H_

#ifdef DW_PLATFORM_WINDOWS

// extern "C" {
Dwarfworks::Core::App::Application* Dwarfworks::Core::App::CreateApplication();
//}

int main(int argc, char** argv) {
  Dwarfworks::Core::Logging::Log::Initialize();

  DW_CORE_WARN("Initialized Log!");
  auto msg = "folks";
  DW_INFO("Hello {0}.", msg);

  auto app = Dwarfworks::Core::App::CreateApplication();
  app->Run();
  delete app;
  return 0;
}

#endif

#endif  // CORE_ENTRY_POINT_H_
