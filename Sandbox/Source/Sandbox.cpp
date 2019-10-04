#include <Dwarfworks.h>

using namespace Dwarfworks::Core;

class Sandbox : public App::Application {
 public:
  Sandbox() = default;
  virtual ~Sandbox() override = default;
};

App::Application* App::CreateApplication() { return new Sandbox(); }
