#include <Dwarfworks.h>

class TestLayer : public Dwarfworks::Layer {
 public:
  TestLayer() : Layer("Test Layer") {}

  void OnUpdate() override { DW_INFO("TestLayer::Update"); }

  void OnEvent(Dwarfworks::Event& event) override {
    DW_TRACE("TestLayer::{0}::OnEvent", event);
  }
};

class AnotherTestLayer : public Dwarfworks::Layer {
 public:
  AnotherTestLayer() : Layer("Another Test Layer") {}

  void OnUpdate() override { DW_INFO("AnotherTestLayer::Update"); }

  void OnEvent(Dwarfworks::Event& event) override {
    DW_TRACE("AnotherTestLayer::{0}::OnEvent", event);
  }
};

class Sandbox : public Dwarfworks::Application {
 public:
  Sandbox() {
    PushLayer(new TestLayer());
    PushLayer(new AnotherTestLayer());
  }

  virtual ~Sandbox() override = default;
};

Dwarfworks::Application* Dwarfworks::CreateApplication() {
  return new Sandbox();
}
