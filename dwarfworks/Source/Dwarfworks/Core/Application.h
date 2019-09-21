#ifndef DWARFWORKS_CORE_APPLICATION_H_
#define DWARFWORKS_CORE_APPLICATION_H_

#include "core.h"

namespace Dwarfworks {
namespace Core {

class DWARF_API Application {
  // represents the state of the application,
  // used to gracefully exit with a message
  enum class State : int { Initialized = 0, Failed = 1, Running = 2 };

  // function is defined inside the client sources
  // holds the logic for creating a new application
  friend Application* CreateApplication();

 public:
  Application();
  virtual ~Application();

  // the application/game main loop
  void Run();

 private:
  State m_State{State::Initialized};

  // checks if the application initialization was 'OK'
  // designed to throw on state != OK
  void ChangeState(const State&) noexcept(false);

  inline bool IsInit() const noexcept { return m_State == State::Initialized; }
  inline bool IsRunning() const noexcept { return m_State == State::Running; }
  inline bool IsFailed() const noexcept { return m_State == State::Failed; }
};

}  // namespace Core
}  // namespace Dwarfworks

#endif  // DWARFWORKS_CORE_APPLICATION_H_
