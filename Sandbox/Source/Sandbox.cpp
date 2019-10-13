#include <Dwarfworks.h>

class TestLayer : public Dwarfworks::Layer {
 public:
  TestLayer() : Layer("Test Layer") {}

  void OnUpdate() override {
    if (Dwarfworks::Input::IsKeyPressed(Dwarfworks::KeyCodes::TAB)) {
      DW_INFO("Tab key is pressed (poll)!");
    }

    if (Dwarfworks::Input::IsMouseButtonPressed(
            Dwarfworks::MouseButtonCodes::BUTTON_LEFT)) {
      const auto [x, y] = Dwarfworks::Input::GetMousePosition();
      DW_INFO("Cursor is at ({0}, {1}).", x, y);
    }
  }

  void OnEvent(Dwarfworks::Event& event) override {
    if (event.GetEventType() == Dwarfworks::EventType::KeyPressed) {
      auto& e = static_cast<Dwarfworks::KeyPressedEvent&>(event);
      if (e.GetKeyCode() == Dwarfworks::KeyCodes::LEFT_CONTROL) {
        DW_TRACE("Ctrl key is pressed (event)!");
      } else {
        DW_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
      }
    }
  }
};

class Sandbox final : public Dwarfworks::Application {
 public:
  Sandbox() {
    PushLayer(new TestLayer());
    PushOverlay(new Dwarfworks::DebugUILayer());
  }

  ~Sandbox() override = default;
};

Dwarfworks::Scope<Dwarfworks::Application> Dwarfworks::CreateApplication() {
  return Dwarfworks::CreateScope<Sandbox>();
}
