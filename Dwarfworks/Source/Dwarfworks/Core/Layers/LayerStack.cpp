#include "dwpch.h"

#include "LayerStack.h"

namespace Dwarfworks {

LayerStack::LayerStack() { m_LayerInsert = m_Layers.begin(); }

LayerStack::~LayerStack() {
  auto deleteLayer = [](Layer* layer) { delete layer; };
  std::for_each(m_Layers.begin(), m_Layers.end(), deleteLayer);
}

void LayerStack::PushLayer(Layer* layer) {
  m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void LayerStack::PushOverlay(Layer* layer) { m_Layers.emplace_back(layer); }

void LayerStack::PopLayer(Layer* layer) {
  if (auto it = DW_FIND(m_Layers, layer); it != m_Layers.end()) {
    m_Layers.erase(it);
    --m_LayerInsert;
  }
}

void LayerStack::PopOverlay(Layer* layer) {
  if (auto it = DW_FIND(m_Layers, layer); it != m_Layers.end()) {
    m_Layers.erase(it);
  }
}

}  // namespace Dwarfworks
