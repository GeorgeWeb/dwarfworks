#ifndef CORE_LAYERS_LAYER_H_
#define CORE_LAYERS_LAYER_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Events/Event.h"

namespace Dwarfworks {

class DW_API Layer {
 public:
  Layer();
  explicit Layer(const std::string& name);

  virtual ~Layer();

  // The virtual members are optional for overriding by
  // the derived layer implementation

  virtual void OnAttach() {}

  virtual void OnDetach() {}

  // virtual void OnAwake() {} // (?)
  // virtual void OnStart() {} // (?)

  virtual void OnFixedUpdate() {}  // TODO: Add Timestep!

  virtual void OnUpdate() {}  // TODO: Add Timestep!

  virtual void OnLateUpdate() {}  // TODO: Add Timestep!

  virtual void OnRender() {}

  virtual void OnDebugUIRender() {}

  virtual void OnEvent(Event& event) {}

  inline const std::string& GetName() const noexcept { return m_DebugName; }

 protected:
  std::string m_DebugName{"Layer"};
};

}  // namespace Dwarfworks

#endif  // CORE_LAYERS_LAYER_H_
