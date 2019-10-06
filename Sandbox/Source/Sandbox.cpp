#include <Dwarfworks.h>

using namespace Dwarfworks;

class Sandbox : public Core::Application {
 public:
  Sandbox() = default;
  virtual ~Sandbox() override = default;
};

Core::Application* Core::CreateApplication() { return new Sandbox(); }
