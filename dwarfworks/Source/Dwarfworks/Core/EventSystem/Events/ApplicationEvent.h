#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_APPLICATION_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_APPLICATION_EVENT_H_

#include "../Event.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

struct DWARF_API ApplicationEvent
    : public EventT<ApplicationEvent, EventCategory::Application> {
  std::string ToString() const { return GetName(); }
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // !DWARFWORKS_CORE_EVENT_SYSTEM_APPLICATION_EVENT_H_
