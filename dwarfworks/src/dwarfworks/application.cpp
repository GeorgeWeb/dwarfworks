#include "application.h"

#include <iostream>
#include <stdexcept>

namespace dwarfworks {

// TODO: implement
application::application() = default;

// TODO: implement
application::~application() = default;

void application::prepare_loop() {
  if (m_state != state::FAILED) {
    m_state = state::RUNNING;
  } else {
    throw std::runtime_error(
        "Issues during engine initialization of the application.");
  }
}

void application::run() {
  try {
    prepare_loop();
    std::cout << "Running <dwarfworks> application." << std::endl;
    while (m_state == state::RUNNING) {
      ;
    }
  } catch (std::exception const& error) {
    std::cout << "Application failed to run." << std::endl;
    std::cout << "Error: " << error.what() << std::endl;
  }
}
}  // namespace dwarfworks
