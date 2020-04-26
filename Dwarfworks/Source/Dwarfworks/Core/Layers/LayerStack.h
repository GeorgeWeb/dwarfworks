#ifndef CORE_LAYERS_LAYER_STACK_H_
#define CORE_LAYERS_LAYER_STACK_H_

#include "Layer.h"

namespace Dwarfworks {

class DW_API LayerStack {
 public:
  LayerStack() = default;
  ~LayerStack();

  // Disable layers movement or copying for the time being
  // for now, layer stacks will only live for one instance (level) of the game
  LayerStack(const LayerStack&) = delete;
  LayerStack& operator==(const LayerStack&) = delete;
  LayerStack(LayerStack&&) = delete;
  LayerStack& operator==(LayerStack&&) = delete;

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);

  void PopLayer(Layer* layer);
  void PopOverlay(Layer* overlay);

  std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
  std::vector<Layer*>::iterator end() { return m_Layers.end(); }

  std::vector<Layer*>::const_iterator begin() const { return m_Layers.cbegin(); }
  std::vector<Layer*>::const_iterator end() const { return m_Layers.cend(); }

  std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
  std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

 private:
  std::vector<Layer*> m_Layers;
  unsigned int m_LayerInsertIndex{0};
};

}  // namespace Dwarfworks

#endif  // CORE_LAYERS_LAYER_STACK_H_
