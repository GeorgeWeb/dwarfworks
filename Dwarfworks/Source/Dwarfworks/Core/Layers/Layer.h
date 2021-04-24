#ifndef CORE_LAYERS_LAYER_H_
#define CORE_LAYERS_LAYER_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Timestep.h"
#include "Dwarfworks/Events/Event.h"

namespace Dwarfworks
{
class ENGINE_API Layer
{
  public:
    Layer() = default;
    explicit Layer(const std::string& name);

    virtual ~Layer() = default;

    // The virtual members are optional for overriding by
    // the derived layer implementation

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    // virtual void OnAwake() {} // (?)
    // virtual void OnStart() {} // (?)

    // virtual void OnFixedUpdate() {}

    virtual void OnUpdate(Timestep deltaTime) {}

    // This is useful to order script execution. For example a follow camera
    // should always be implemented in LateUpdate because it tracks objects that
    // might have moved inside Update.
    // virtual void OnLateUpdate() {}

    virtual void OnRender() {}

    virtual void OnDebugUIRender() {}

    virtual void OnEvent(Event& event) {}

    inline const std::string& GetName() const noexcept { return m_DebugName; }

    virtual bool IsOverlay() const { return false; }

  protected:
    std::string m_DebugName {"Layer"};
};

} // namespace Dwarfworks

#endif // CORE_LAYERS_LAYER_H_
