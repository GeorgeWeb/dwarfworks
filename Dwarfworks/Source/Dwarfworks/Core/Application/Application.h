#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include "../Core.h"
#include "../Window/Window.h"

namespace Dwarfworks {
namespace Core {

class DW_API Application {
 public:
  Application() = default;
  virtual ~Application() = default;

  // the application/game main loop
  void Run();

 protected:
  inline bool IsRunning() const noexcept { return m_IsRunning; }

 private:
  bool m_IsRunning{false};
};

Application* CreateApplication();

}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_APPLICATION_APPLICATION_H_
