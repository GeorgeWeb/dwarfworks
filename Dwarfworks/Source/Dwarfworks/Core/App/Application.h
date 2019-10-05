#ifndef CORE_APP_APPLICATION_H_
#define CORE_APP_APPLICATION_H_

#include "../Core.h"

namespace Dwarfworks {
namespace Core {
namespace App {

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

// declaration only
extern "C" {
Application* CreateApplication();
}

}  // namespace App
}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_APP_APPLICATION_H_
