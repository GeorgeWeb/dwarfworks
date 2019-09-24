#include "Application.h"
#include "EventSystem/Events/ApplicationEvent.h"
#include "EventSystem/Events/UncategorizedEvent.h"

#include <stdexcept>
#include "Log.h"

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
    DWARF_CORE_INFO("Running <dwarfworks> application.");
    EventDispatcher disp(ApplicationEvent{});
    ApplicationEvent appEvnt{};

    // evntDisp.Dispatch(f(appEvnt));

    if (appEvnt.IsInCategory(EventCategory::Application)) {
      DWARF_CORE_INFO("{0} is in Application category", appEvnt.GetName());
    }

    // testing events comparison
    UncategorizedEvent otherEvnt{};
    if (appEvnt == otherEvnt) {
      // Do something ...
    }

    while (IsRunning()) {
      // handle main loop
    }
  } catch (std::exception const& error) {
    DWARF_CORE_ERROR("Application runtime has failed.");
    DWARF_CORE_ERROR("Error: {0}.", error.what());
  }
}

}  // namespace Core
}  // namespace Dwarfworks
