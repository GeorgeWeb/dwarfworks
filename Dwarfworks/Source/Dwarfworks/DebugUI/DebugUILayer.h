#ifndef DEBUGUI_DEBUGUI_LAYER_H_
#define DEBUGUI_DEBUGUI_LAYER_H_

#include "../Core/Layers/Layer.h"

namespace Dwarfworks {

class DebugUILayer final : public Layer {
 public:
  /// \fn final::DebugUILayer();
  ///
  /// \brief Default constructor
  ///
  /// \author Georg
  /// \date 08/10/2019

  DebugUILayer();

  /// \fn final::~DebugUILayer() override final;
  ///
  /// \brief Destructor
  ///
  /// \author Georg
  /// \date 08/10/2019

  ~DebugUILayer() override final;

  /// \fn void final::OnAttach() override final;
  ///
  /// \brief Executes the attach action
  ///
  /// \author Georg
  /// \date 08/10/2019

  void OnAttach() override final;

  /// \fn void final::OnDetach() override final;
  ///
  /// \brief Executes the detach action
  ///
  /// \author Georg
  /// \date 08/10/2019

  void OnDetach() override final;

  /// \fn void final::OnUpdate() override final;
  ///
  /// \brief Executes the update action
  ///
  /// \author Georg
  /// \date 08/10/2019

  void OnUpdate() override final;

  /// \fn void final::OnEvent(Event& event) override final;
  ///
  /// \brief Executes the event action
  ///
  /// \author Georg
  /// \date 08/10/2019
  ///
  /// \param [in,out] event The event.

  void OnEvent(Event& event) override final;

 private:
};

}  // namespace Dwarfworks

#endif  // !DEBUGUI_DEBUGUI_LAYER_H_
