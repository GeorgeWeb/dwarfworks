#include <Dwarfworks.h>

using namespace Dwarfworks;

class Sandbox : public Application {
 public:
  Sandbox() = default;
  virtual ~Sandbox() override = default;
};

Application* CreateApplication() { return new Sandbox(); }
