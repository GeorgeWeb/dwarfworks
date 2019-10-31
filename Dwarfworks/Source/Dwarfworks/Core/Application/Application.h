#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "Dwarfworks/Core/Core.h"

// Window
#include "Dwarfworks/Core/Window/IWindow.h"

// Layers
#include "Dwarfworks/Core/Layers/LayerStack.h"
#include "Dwarfworks/DebugUI/DebugUILayer.h"

// Events
#include "Dwarfworks/Events/ApplicationEvent.h"

#ifdef ENABLE_VISUAL_TESTING
#include "Testing/Test.h"
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
  Application();
  virtual ~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  // Gets the Application singleton instance
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

  // The application/game main loop
  void Run();

  // Executes the event action
  void OnEvent(Event& event);

  // Query if the application is running
  inline bool IsRunning() const noexcept { return m_IsRunning; }

  // Pushes a layer
  void PushLayer(Layer* layer);
  // Pushes an overlay
  void PushOverlay(Layer* layer);

  // Gets the window for the user's platform
  inline IWindow& GetWindow() const { return *m_Window; }

 private:
  // Executes the window closed action
  // True if it succeeds, false if it fails.
  bool OnWindowClosed(WindowCloseEvent& event);

 private:
  Scope<IWindow> m_Window;
  Ref<DebugUILayer> m_DebugUILayer;

  bool m_IsRunning{true};
  LayerStack m_LayerStack;

 private:  // testing on/off
#ifdef ENABLE_VISUAL_TESTING
  inline static Testing::Test* m_CurrentTest = nullptr;
  Ref<Testing::TestMenu> m_TestMenu;
#endif

 private:  // singleton-related variable members
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
