#ifndef DEBUGUI_DEBUGUI_LAYER_H_
#define DEBUGUI_DEBUGUI_LAYER_H_

#include "Dwarfworks/Core/Layers/Layer.h"

#include "Dwarfworks/Events/ApplicationEvent.h"
#include "Dwarfworks/Events/KeyEvent.h"
#include "Dwarfworks/Events/MouseEvent.h"

namespace Dwarfworks {

class DW_API DebugUILayer final : public Layer {
 public:
  /// \fn final::DebugUILayer();
  ///
  /// \brief Default constructor
  ///
  /// \author Georg
  /// \date 08/10/2019

  DebugUILayer();

  ~DebugUILayer() = default;

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

  /// \fn void final::OnDebugUIRender() override final;
  ///
  /// \brief Executes the debug user interface render action
  ///
  /// \author Georg
  /// \date 13/10/2019

  void OnDebugUIRender() override final;

  /// \fn void final::Begin() const;
  ///
  /// \brief Begins this object
  ///
  /// \author Georg
  /// \date 13/10/2019

  void Begin() const;

  /// \fn void final::End() const;
  ///
  /// \brief Ends this object
  ///
  /// \author Georg
  /// \date 13/10/2019

  void End() const;

 private:
  float m_Time{0.0f};
};

}  // namespace Dwarfworks

#endif  // !DEBUGUI_DEBUGUI_LAYER_H_
