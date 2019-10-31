// begin PCH
#include "dwpch.h"
// end PCH

#include "Layer.h"

namespace Dwarfworks {

Layer::Layer() {
  // ...
}

Layer::Layer(const std::string& name) : m_DebugName(name) {}

Layer::~Layer() {
  // ...
}

}  // namespace Dwarfworks
