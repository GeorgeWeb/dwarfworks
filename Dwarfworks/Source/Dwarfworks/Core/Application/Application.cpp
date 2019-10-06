#include "dwpch.h"

#include "Application.h"

// ...
#include "../Log/Log.h"

// ...
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
// ...
#include "../Events/EventDispatcher.h"

namespace Dwarfworks {

Application::Application() = default;

Application::~Application() = default;

void Application::Run() {
  m_IsRunning = true;

  DW_CORE_INFO("Running <dwarfworks> application.");

  // fix by creating an empty event
  EventManager eventManager(/*empty_event*/ AppFixedUpdateEvent{});

  eventManager.Register(AppUpdateEvent{});
  AppUpdateEvent appEvnt{};
  DW_TRACE(appEvnt);

  // testing event category check
  if (appEvnt.IsInCategory(EventCategoryInput)) {
    DW_TRACE("Yes, {0} is in EventCategoryInput", appEvnt);
  } else {
    DW_WARN("No, {0} is NOT in EventCategoryInput", appEvnt);
  }

  // testing events comparison
  AppUpdateEvent otherEvnt{};
  if (appEvnt == otherEvnt) {
    DW_TRACE("{0} equals {1}", appEvnt, otherEvnt);
  } else {
    DW_WARN("{0} are NOT {1} the same", appEvnt, otherEvnt);
  }

  AppRenderEvent anotherEvnt{};
  if (otherEvnt == anotherEvnt) {
    DW_TRACE("{0} equals {1}", otherEvnt, anotherEvnt);
  } else {
    DW_WARN("{0} and {1} are NOT the same", otherEvnt, anotherEvnt);
  }
  WindowResizeEvent winEvnt(1280, 720);
  DW_TRACE(winEvnt);

  // Window tests
  // auto windowPtr = Window::Create();

  // the main loop
  while (IsRunning()) {
    // handle main loop
  }
}

}  // namespace Dwarfworks
