#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include "../Core.h"
#include "../Window/Window.h"

namespace Dwarfworks {

class DW_API Application {
 public:
  Application();
  virtual ~Application();

  // the application/game main loop
  void Run();

 protected:
  inline bool IsRunning() const noexcept { return m_IsRunning; }

 private:
  bool m_IsRunning{false};
};

Application* CreateApplication();

}  // namespace Dwarfworks

#endif  // CORE_APPLICATION_APPLICATION_H_
