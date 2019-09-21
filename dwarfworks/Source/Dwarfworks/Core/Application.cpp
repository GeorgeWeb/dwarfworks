#include "Application.h"

#include <iostream>
#include <stdexcept>

namespace Dwarfworks {
namespace Core {

// TODO: implement
Application::Application() = default;

// TODO: implement
Application::~Application() = default;

void Application::ChangeState(const State& state) noexcept(false) {
  if (!IsFailed()) {
    m_State = state;
  } else {
    throw std::runtime_error(
        "The Application has failed to initialize state [insert state here].");
  }
}

void Application::Run() {
  try {
    ChangeState(State::Running);
    std::cout << "Running <dwarfworks> application." << std::endl;
    while (IsRunning()) {
      // handle main loop
    }
  } catch (std::exception const& error) {
    std::cout << "Application runtime has failed." << std::endl;
    std::cout << "Error: " << error.what() << std::endl;
  }
}

}  // namespace Core
}  // namespace Dwarfworks
