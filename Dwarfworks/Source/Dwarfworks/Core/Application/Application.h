#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "../Core.h"
#include "../Window/Window.h"

namespace Dwarfworks {

/// \class Application
///
/// \brief An api.
///
/// \author Georg
/// \date 07/10/2019

class DW_API Application {
 public:
  /// \fn Application::Application();
  ///
  /// \brief Default constructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  Application();

  /// \fn virtual Application::~Application();
  ///
  /// \brief Destructor.
  ///
  /// \author Georg
  /// \date 07/10/2019

  virtual ~Application();

  /// \fn void Application::Run();
  ///
  /// \summary the application/game main loop.
  ///
  /// \author Georg
  /// \date 07/10/2019

  void Run();

 protected:
  /// \fn inline bool Application::IsRunning() const noexcept
  ///
  /// \brief Query if this object is running.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns True if running, false if not.

  inline bool IsRunning() const noexcept { return m_IsRunning; }

 private:
  /// \brief True if is running, false if not.
  bool m_IsRunning{true};

  /// \brief The window.
  std::unique_ptr<Window> m_Window;
};

/// \fn Dwarfworks::Application* CreateApplication();
///
/// \brief Creates the application.
///
/// \author Georg
/// \date 07/10/2019
///
/// \returns Null if it fails, else the new application.

Dwarfworks::Application* CreateApplication();

}  // namespace Dwarfworks

#endif  // CORE_APPLICATION_APPLICATION_H_
