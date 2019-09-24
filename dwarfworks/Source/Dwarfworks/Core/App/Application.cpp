#include "Application.h"

// ...
#include "../Logging/Log.h"

// ...
#include "../EventSystem/Events/ApplicationEvent.h"
#include "../EventSystem/Events/KeyEvent.h"
#include "../EventSystem/Events/MouseEvent.h"
#include "../EventSystem/Events/UncategorizedEvent.h"
// ...
#include "../EventSystem/EventDispatcher.h"

#include <stdexcept>

namespace Dwarfworks {
namespace Core {
namespace App {

void Application::Run() {
  using namespace EventSystem;

  m_IsRunning = true;

  try {
    DWARF_CORE_INFO("Running <dwarfworks> application.");
    EventDispatcher disp(ApplicationEvent{});
    ApplicationEvent appEvnt{};

    // evntDisp.Dispatch(f(appEvnt));

    // testing event category check
    if (appEvnt.IsInCategory(EventCategory::Input)) {
      DWARF_CORE_INFO("Yes, {0} is in Application category", appEvnt.GetName());
    } else {
      DWARF_CORE_WARN("No, {0} is NOT in Application category",
                      appEvnt.GetName());
    }

    // testing events comparison
    ApplicationEvent otherEvnt{};
    if (appEvnt == otherEvnt) {
      // Do something ...
    }
    UncategorizedEvent otherEvnt2{};
    if (appEvnt == otherEvnt2) {
      // Do something ...
    }

    MouseMovedEvent mouseEvnt1(100, 100);
    DWARF_TRACE("{0}", mouseEvnt1.ToString());

    MouseButtonPressedEvent mouseEvnt2(1);
    DWARF_TRACE("{0}", mouseEvnt2.ToString());

    // the main loop
    while (IsRunning()) {
      // handle main loop
    }

    // post-mainloop (some non RAII cleanup, !not recommended!)
  } catch (std::exception const& error) {
    DWARF_CORE_ERROR("Application runtime has failed.");
    DWARF_CORE_ERROR("Error: {0}.", error.what());
  }
}

}  // namespace App
}  // namespace Core
}  // namespace Dwarfworks
