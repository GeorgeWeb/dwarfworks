#include <Dwarfworks.h>

class TestLayer : public Dwarfworks::Layer {
 public:
  TestLayer() : Layer("Test Layer") {}

  void OnUpdate() override { DW_INFO("TestLayer::Update"); }

  void OnEvent(Dwarfworks::Event& event) override {
    DW_TRACE("TestLayer::{0}::OnEvent", event);
  }
};

class Sandbox final : public Dwarfworks::Application {
 public:
  Sandbox() {
    PushLayer(new TestLayer());
    PushOverlay(new Dwarfworks::DebugUILayer());
  }

  /*
  void Initialise() override {
    // ...
    Dwarfworks::Application::Initialise();
  }
  */

  ~Sandbox() override = default;
};

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication() {
  return Dwarfworks::CreateScope<Sandbox>();
}
