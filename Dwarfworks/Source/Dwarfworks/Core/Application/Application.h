#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "Dwarfworks/Core/Core.h"

// Window
#include "Dwarfworks/Core/Window/IWindow.h"

// Layers
#include "Dwarfworks/Core/Layers/LayerStack.h"
#include "Dwarfworks/DebugUI/DebugUILayer.h"

// Events
#include "Dwarfworks/Core/Events/ApplicationEvent.h"

#include <atomic>
#include <mutex>

#ifdef ENABLE_VISUAL_TESTING
// forward decl.
namespace Tests {
class Test;
class TestMenu;
}  // namespace Tests
#endif

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

  virtual ~Application() = default;

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  /// \fn inline static Application& Application::Get()
  ///
  /// \brief Gets the Application singleton instance
  ///
  /// \author Georg
  /// \date 12/10/2019
  ///
  /// \returns A reference to an Application.

  inline static Application& Get() {
    // Acquire-Release semantic for C++ atomics (standard thread-safe guarantee)
    // https://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton

    // acquire: no reads or writes in the current thread can be reordered before
    // this load
    auto instance = s_Instance.load(std::memory_order_acquire);
    // Double-checked locking pattern
    if (!instance) {
      std::scoped_lock<std::mutex> lock(s_Mutex);
      // no synchronization or ordering constraints imposed on other reads or
      // writes, only this operation's atomicity is guaranteed
      instance = s_Instance.load(std::memory_order_relaxed);
      if (!instance) {
        instance = new Application();
        // release: no reads or writes in the current thread can be reordered
        // after this store
        s_Instance.store(instance, std::memory_order_release);
      }
    }
    return *instance;
  }

  /// \fn void Application::Run();
  ///
  /// \summary the application/game main loop.
  ///
  /// \author Georg
  /// \date 07/10/2019

  void Run();

  /// \fn void Application::OnEvent(Event& event);
  ///
  /// \brief Executes the event action
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] event The event.

  void OnEvent(Event& event);

  /// \fn inline bool Application::IsRunning() const noexcept
  ///
  /// \brief Query if this object is running.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns True if running, false if not.

  inline bool IsRunning() const noexcept { return m_IsRunning; }

  /// \fn void Application::PushLayer(Layer* layer);
  ///
  /// \brief Pushes a layer
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] layer If non-null, the layer.

  void PushLayer(Layer* layer);

  /// \fn void Application::PushOverlay(Layer* layer);
  ///
  /// \brief Pushes an overlay
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] layer If non-null, the layer.

  void PushOverlay(Layer* layer);

  /// \fn inline Window& Application::GetWindow() const
  ///
  /// \brief Gets the window
  ///
  /// \author Georg
  /// \date 12/10/2019
  ///
  /// \returns The window.

  inline IWindow& GetWindow() const { return *m_Window; }

 private:
  /// \fn bool Application::OnWindowClosed(WindowCloseEvent& event);
  ///
  /// \brief Executes the window closed action
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \param [in,out] event The event.
  ///
  /// \returns True if it succeeds, false if it fails.

  bool OnWindowClosed(WindowCloseEvent& event);

 private:
  Scope<IWindow> m_Window;
  Ref<DebugUILayer> m_DebugUILayer;

  bool m_IsRunning{true};
  LayerStack m_LayerStack;

#ifdef ENABLE_VISUAL_TESTING
  Tests::Test* m_CurrentTest = nullptr;
  Ref<Tests::TestMenu> m_TestMenu;
#endif

  static std::atomic<Application*> s_Instance;
  static std::mutex s_Mutex;
};

/// \fn Dwarfworks::Application* CreateApplication();
///
/// \brief Creates the application.
///
/// \author Georg
/// \date 07/10/2019
///
/// \returns Null if it fails, else the new application.

Scope<Dwarfworks::Application> CreateApplication();

}  // namespace Dwarfworks

#endif  // CORE_APPLICATION_APPLICATION_H_
