#ifndef DEBUGUI_DEBUGUI_LAYER_H
#define DEBUGUI_DEBUGUI_LAYER_H

#include "Dwarfworks/Core/Layer/Layer.h"
#include "Dwarfworks/Event/ApplicationEvent.h"
#include "Dwarfworks/Event/KeyEvent.h"
#include "Dwarfworks/Event/MouseEvent.h"

namespace Dwarfworks
{
class ENGINE_API DebugUILayer final : public Layer
{
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
    float m_Time {0.0f};
    bool  m_Overlay = true;
};

} // namespace Dwarfworks

#endif // !DEBUGUI_DEBUGUI_LAYER_H
