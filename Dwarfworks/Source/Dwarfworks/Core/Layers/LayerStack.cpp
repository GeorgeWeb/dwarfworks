#include "dwpch.h"

#include "LayerStack.h"

namespace Dwarfworks {

LayerStack::~LayerStack() {
  for (auto layer : m_Layers) {
    layer->OnDetach();
    delete layer;
  }
}

void LayerStack::PushLayer(Layer* layer) {
  m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
  m_LayerInsertIndex++;
  layer->OnAttach();
}

void LayerStack::PushOverlay(Layer* overlay) {
  m_Layers.emplace_back(overlay);
  overlay->OnAttach();
}

void LayerStack::PopLayer(Layer* layer) {
  if (auto it = DW_FIND(m_Layers, layer); it != m_Layers.end()) {
    layer->OnDetach();
    m_Layers.erase(it);
    m_LayerInsertIndex--;
  }
}

void LayerStack::PopOverlay(Layer* overlay) {
  if (auto it = DW_FIND(m_Layers, overlay); it != m_Layers.end()) {
    overlay->OnDetach();
    m_Layers.erase(it);
  }
}

}  // namespace Dwarfworks
