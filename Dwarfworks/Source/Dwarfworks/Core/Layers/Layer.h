#ifndef CORE_LAYERS_LAYER_H_
#define CORE_LAYERS_LAYER_H_

#include "../Core.h"
#include "../Events/Event.h"

namespace Dwarfworks {

/// \class Layer
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API Layer {
 public:
  /// \fn Layer::Layer();
  ///
  /// \brief Default constructor
  ///
  /// \author Georg
  /// \date 07/10/2019

  Layer();

  /// \fn explicit Layer::Layer(const std::string& name);
  ///
  /// \brief Constructor
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param name The name.

  explicit Layer(const std::string& name);

  /// \fn virtual Layer::~Layer();
  ///
  /// \brief Destructor
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual ~Layer();

  // The virtual members are optional for overriding by
  // the derived layer implementation

  /// \fn virtual void Layer::OnAttach()
  ///
  /// \brief Executes the attach action
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual void OnAttach() {}

  /// \fn virtual void Layer::OnDetach()
  ///
  /// \brief Executes the detach action
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual void OnDetach() {}

  /// \fn virtual void Layer::OnUpdate()
  ///
  /// \brief Executes the update action
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual void OnUpdate() {}  // TODO: Add Timestep!

  /// \fn virtual void Layer::OnDebugUIRender()
  ///
  /// \brief Executes the DebugUI graphical user interface render action
  ///
  /// \author Georg
  /// \date 13/10/2019

  virtual void OnDebugUIRender() {}

  /// \fn virtual void Layer::OnEvent(Event& event)
  ///
  /// \brief Executes the event action
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] event The event.

  virtual void OnEvent(Event& event) {}

  /// \fn inline const std::string& Layer::GetName() const noexcept
  ///
  /// \brief Gets the name
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The name.

  inline const std::string& GetName() const noexcept { return m_DebugName; }

 protected:
  /// \brief Name of the debug
  std::string m_DebugName{"Layer"};
};

}  // namespace Dwarfworks

#endif  // CORE_LAYERS_LAYER_H_
