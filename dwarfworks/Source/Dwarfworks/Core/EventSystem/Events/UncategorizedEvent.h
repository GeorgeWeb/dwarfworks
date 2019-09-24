#ifndef DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_UNCATEGORIZED_EVENT_H_
#define DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_UNCATEGORIZED_EVENT_H_

#include "../Event.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

// Default event declaration (& definition) for UncategorizedEvent.
struct DWARF_API UncategorizedEvent
    : public EventT<UncategorizedEvent, EventCategory::Uncategorized> {};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // !DWARFWORKS_CORE_EVENT_SYSTEM_EVENTS_UNCATEGORIZED_EVENT_H_
