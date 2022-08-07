// begin PCH
#include "dwpch.h"
// end PCH

#include "Layer.h"

using namespace Dwarfworks;

Layer::Layer() : m_DebugName {"Layer"}
{
}

Layer::Layer(const std::string& name) : m_DebugName {name}
{
}
