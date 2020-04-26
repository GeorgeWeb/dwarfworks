#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "Dwarfworks/Core/Core.h"

// Window
#include "Dwarfworks/Core/Window/Window.h"

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

  // Application is non-copyable and non-movable(for now)
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  // Gets the Application singleton instance
  inline static Application& Get() {
	// attempts a safer thread-safe singleton instance than than static guarante
	//
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

  // The application/game loop
  virtual void GameLoop();
  
  // The application/game loop with built-in
  // TestMenu Layer for graphics testing purposes
  void DebugGameLoop();

  // Executes the event action
  virtual void OnEvent(Event& event);

  // Query if the application is running
  inline bool IsRunning() const noexcept { return m_IsRunning; }
  // Set the application running state
  inline void SetRunning(bool isRunning) { m_IsRunning = isRunning; }

  // ...
  inline float GetLastFrameTime() const noexcept { return m_LastFrameTime; }

  // return the frames per second calculated in the Run loop

  // Pushes a layer
  void PushLayer(Layer* layer);
  // Pushes an overlay
  void PushOverlay(Layer* layer);

  // Gets the window for the user's platform
  inline Window& GetWindow() const { return *m_Window; }

 protected:
  // Executes the window closed action
  // True if it succeeds, false if it fails.
  virtual bool OnWindowClosed(WindowCloseEvent& event);

 protected:
  Scope<Window> m_Window;
  Ref<DebugUILayer> m_DebugUILayer;
  LayerStack m_LayerStack;
  
private:
  bool m_IsRunning = true;
  // timestep
  float m_LastFrameTime = 0.0f;

 private:  // testing on/off
#ifdef ENABLE_VISUAL_TESTING
  inline static Testing::Test* m_CurrentTest = nullptr;
  Ref<Testing::TestMenu> m_TestMenu;
#endif

  // singleton-related variable members
  static std::atomic<Application*> s_Instance;
  static std::mutex s_Mutex;
};

Dwarfworks::Application* CreateApplication();

}  // namespace Dwarfworks

#endif  // CORE_APPLICATION_APPLICATION_H_
