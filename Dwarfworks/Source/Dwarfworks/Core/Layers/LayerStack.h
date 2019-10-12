#ifndef CORE_LAYERS_LAYER_STACK_H_
#define CORE_LAYERS_LAYER_STACK_H_

#include "Layer.h"

namespace Dwarfworks {

/// \class LayerStack
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API LayerStack {
 public:
  /// \fn LayerStack::LayerStack();
  ///
  /// \brief Default constructor
  ///
  /// \author Georg
  /// \date 07/10/2019

  LayerStack();

  /// \fn LayerStack::~LayerStack();
  ///
  /// \brief Destructor
  ///
  /// \author Georg
  /// \date 07/10/2019

  ~LayerStack();

  // disable layers movement or copying for the time being
  // for now, layer stacks will only live for one instance (level) of the game

  /// \fn LayerStack::LayerStack(const LayerStack&) = delete;
  ///
  /// \brief Copy constructor
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param parameter1 The first parameter.

  LayerStack(const LayerStack&) = delete;

  /// \fn LayerStack& LayerStack::operator==(const LayerStack&) = delete;
  ///
  /// \brief Equality operator
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param parameter1 The first parameter.
  ///
  /// \returns True if the parameters are considered equivalent.

  LayerStack& operator==(const LayerStack&) = delete;

  /// \fn LayerStack::LayerStack(LayerStack&&) = delete;
  ///
  /// \brief Move constructor
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] parameter1 The first parameter.

  LayerStack(LayerStack&&) = delete;

  /// \fn LayerStack& LayerStack::operator==(LayerStack&&) = delete;
  ///
  /// \brief Equality operator
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] parameter1 The first parameter.
  ///
  /// \returns True if the parameters are considered equivalent.

  LayerStack& operator==(LayerStack&&) = delete;

  /// \fn void LayerStack::PushLayer(Layer* layer);
  ///
  /// \brief Pushes a layer
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] layer If non-null, the layer.

  void PushLayer(Layer* layer);

  /// \fn void LayerStack::PushOverlay(Layer* layer);
  ///
  /// \brief Pushes an overlay
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] layer If non-null, the layer.

  void PushOverlay(Layer* layer);

  /// \fn void LayerStack::PopLayer(Layer* layer);
  ///
  /// \brief Pops the layer described by layer
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] layer If non-null, the layer.

  void PopLayer(Layer* layer);

  /// \fn void LayerStack::PopOverlay(Layer* layer);
  ///
  /// \brief Pops the overlay described by layer
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] layer If non-null, the layer.

  void PopOverlay(Layer* layer);

  /// \fn std::vector<Layer*>::iterator LayerStack::begin()
  ///
  /// \brief Gets the begin
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns Null if it fails, else a std::vector&lt;Layer*&gt;::iterator.

  std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

  /// \fn std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
  ///
  /// \brief Gets the rbegin
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns Null if it fails, else a
  /// std::vector&lt;Layer*&gt;::reverse_iterator.

  std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }

  /// \fn std::vector<Layer*>::iterator LayerStack::end()
  ///
  /// \brief Gets the end
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns Null if it fails, else a std::vector&lt;Layer*&gt;::iterator.

  std::vector<Layer*>::iterator end() { return m_Layers.end(); }

  /// \fn std::vector<Layer*>::reverse_iterator LayerStack::rend()
  ///
  /// \brief Gets the rend
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns Null if it fails, else a
  /// std::vector&lt;Layer*&gt;::reverse_iterator.

  std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

 private:
  /// \brief The layers
  std::vector<Layer*> m_Layers;
  /// \brief The layer insert
  std::vector<Layer*>::iterator m_LayerInsert;
};

}  // namespace Dwarfworks

#endif  // CORE_LAYERS_LAYER_STACK_H_
