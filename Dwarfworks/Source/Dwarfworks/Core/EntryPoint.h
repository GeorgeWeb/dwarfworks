#ifndef CORE_ENTRY_POINT_H_
#define CORE_ENTRY_POINT_H_

#ifdef DW_PLATFORM_WINDOWS

extern Dwarfworks::Application* Dwarfworks::CreateApplication();

/// <summary>	Main entry-point for an application. </summary>
///
/// <remarks>	Georg, 07/10/2019. </remarks>
///
/// <param name="argc">	The number of command-line arguments provided. </param>
/// <param name="argv">	An array of command-line argument strings. </param>
///
/// <returns>	Exit-code for the process - 0 for success, else an error code.
/// </returns>

auto main() -> void {
  Dwarfworks::Log::Initialize();

  auto app = Dwarfworks::CreateApplication();
  app->Run();
  delete app;
}

#endif

#endif  // CORE_ENTRY_POINT_H_
