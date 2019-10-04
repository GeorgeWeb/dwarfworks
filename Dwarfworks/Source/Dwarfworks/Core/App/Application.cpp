#include "dwpch.h"

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

namespace Dwarfworks {
namespace Core {
namespace App {

void Application::Run() {
  using namespace EventSystem;

  m_IsRunning = true;

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
}

}  // namespace App
}  // namespace Core
}  // namespace Dwarfworks
