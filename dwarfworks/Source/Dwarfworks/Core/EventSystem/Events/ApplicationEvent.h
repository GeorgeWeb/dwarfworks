#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_APPLICATION_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_APPLICATION_EVENT_H_

#include "../Event.h"

namespace Dwarfworks {
namespace Core {

struct DWARF_API ApplicationEvent
    : public EventT<ApplicationEvent, EventCategory::Application> {
  std::string ToString() const { return GetName(); }
};

}  // namespace Core
}  // namespace Dwarfworks

#endif  // !DWARFWORKS_CORE_EVENT_SYSTEM_DEFAULT_EVENTS_APPLICATION_EVENT_H_
