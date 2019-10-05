#ifndef CORE_EVENT_SYSTEM_EVENTS_UNCATEGORIZED_EVENT_H_
#define CORE_EVENT_SYSTEM_EVENTS_UNCATEGORIZED_EVENT_H_

#include "../Event.h"

namespace Dwarfworks {
namespace Core {
namespace EventSystem {

// Default event declaration (& definition) for UncategorizedEvent.
class DW_API UncategorizedEvent
    : public EventT<UncategorizedEvent, EventCategory::Uncategorized> {
 public:
  UncategorizedEvent() = default;

  std::string ToString() const { return GetName(); }
};

}  // namespace EventSystem
}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_EVENT_SYSTEM_EVENTS_UNCATEGORIZED_EVENT_H_
