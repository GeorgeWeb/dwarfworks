#include <Dwarfworks.h>

class Sandbox : public Dwarfworks::Core::Application {
 public:
  Sandbox() = default;
  virtual ~Sandbox() override = default;
};

Dwarfworks::Core::Application* Dwarfworks::Core::CreateApplication() {
  // ...
  return new Sandbox();
}
