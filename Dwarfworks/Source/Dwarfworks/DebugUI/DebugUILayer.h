#ifndef DEBUGUI_DEBUGUI_LAYER_H_
#define DEBUGUI_DEBUGUI_LAYER_H_

#include "Dwarfworks/Core/Layers/Layer.h"
#include "Dwarfworks/Events/ApplicationEvent.h"
#include "Dwarfworks/Events/KeyEvent.h"
#include "Dwarfworks/Events/MouseEvent.h"

namespace Dwarfworks {

class DW_API DebugUILayer final : public Layer {
 public:
  DebugUILayer();

  virtual ~DebugUILayer() override final = default;

  virtual void OnAttach() override final;

  virtual void OnDetach() override final;

  virtual void OnDebugUIRender() override final;

  virtual bool IsOverlay() const override final { return m_Overlay; }

  void Begin() const;
  void End() const;

 private:
  float m_Time{0.0f};
  bool m_Overlay = true;
};

}  // namespace Dwarfworks

#endif  // !DEBUGUI_DEBUGUI_LAYER_H_
