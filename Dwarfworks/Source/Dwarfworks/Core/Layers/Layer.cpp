#include "dwpch.h"

#include "Layer.h"

namespace Dwarfworks {

Layer::Layer() = default;

Layer::Layer(const std::string& name) : m_DebugName(name) {}

Layer::~Layer() {}

}  // namespace Dwarfworks
