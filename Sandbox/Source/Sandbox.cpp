#include <Dwarfworks.h>

class Sandbox : public Dwarfworks::Application {
 public:
  Sandbox() = default;
  virtual ~Sandbox() override = default;
};

Dwarfworks::Application* Dwarfworks::CreateApplication() {
  return new Sandbox();
}
