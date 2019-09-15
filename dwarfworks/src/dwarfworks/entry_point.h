#ifndef DWARFWORKS_ENTRY_POINT_H_
#define DWARFWORKS_ENTRY_POINT_H_

#ifdef DWARFWORKS_PLATFORM_WINDOWS

extern dwarfworks::application* dwarfworks::create_app();

int main(int argc, char** argv) {
  dwarfworks::log::init();
  // dwarfworks::log::get_core_logger()->warn("Initialized Log!");
  // dwarfworks::log::get_client_logger()->warn("Initialized Log!");

  auto app = dwarfworks::create_app();
  app->run();
  delete app;
  return 0;
}

#endif  // DWARFWORKS_PLATFORM_WINDOWS

#endif  // DWARFWORKS_ENTRY_POINT_H_
