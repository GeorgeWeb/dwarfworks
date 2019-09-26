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
    EventDispatcher disp(UpdateEvent{});
    UpdateEvent appEvnt{};
    DWARF_TRACE(appEvnt);

    // testing event category check
    if (appEvnt.IsInCategory(EventCategory::Input)) {
      DWARF_TRACE("Yes, {0} is in Application category", appEvnt);
    } else {
      DWARF_WARN("No, {0} is NOT in Application category", appEvnt);
    }

    // testing events comparison
    UpdateEvent otherEvnt{};
    if (appEvnt == otherEvnt) {
      DWARF_TRACE("{0} equals {1}", appEvnt, otherEvnt);
    } else {
      DWARF_WARN("{0} are NOT {1} the same", appEvnt, otherEvnt);
    }

    RenderEvent anotherEvnt{};
    if (otherEvnt == anotherEvnt) {
      DWARF_TRACE("{0} equals {1}", otherEvnt, anotherEvnt);
    } else {
      DWARF_WARN("{0} are NOT {1} the same", otherEvnt, anotherEvnt);
    }
    WindowResizeEvent winEvnt(1280, 720);
    DWARF_TRACE(winEvnt);

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
