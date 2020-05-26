#include "Basic3D.h"

// Debug GUI
#include <imgui/imgui.h>

Basic3D::Basic3D() : SandboxLayer("Basic 3D Things") {
#if 0
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      // positions  // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
  };
  uint32_t indices[] = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
#endif
}

void Basic3D::OnUpdate(Dwarfworks::Timestep deltaTime) {
  // Poll user input
  // ---------------

  // Animate objects
  // ---------------

  // update camera
  // ...
}

void Basic3D::OnRender() {
  // clear buffers - Framebuffer abstraction (TODO!)
  Dwarfworks::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
  Dwarfworks::RenderCommand::SetViewport(
      Dwarfworks::Application::Get().GetWindow().GetWidth() / 2, 0,
      Dwarfworks::Application::Get().GetWindow().GetWidth() / 2,
      Dwarfworks::Application::Get().GetWindow().GetHeight());
  Dwarfworks::RenderCommand::SetScissor(
      Dwarfworks::Application::Get().GetWindow().GetWidth() / 2, 0,
      Dwarfworks::Application::Get().GetWindow().GetWidth() / 2,
      Dwarfworks::Application::Get().GetWindow().GetHeight());
  Dwarfworks::RenderCommand::SetScissorTest();
  Dwarfworks::RenderCommand::Clear();

  // Begin scene rendering
  // ...
  // End scene rendering
}

void Basic3D::OnDebugUIRender() {
  ImGui::Begin((GetName() + " editor").c_str());
  // ...
  ImGui::End();
}

void Basic3D::OnEvent(Dwarfworks::Event& event) {
  // ...
  Dwarfworks::EventManager eventManager(event);

#if 0
  if (event.GetEventType() == Dwarfworks::EventType::WindowResize) {
    DW_WARN("Sandbox::WindowResize");
    auto& re = static_cast<Dwarfworks::WindowResizeEvent&>(event);

    // TODO: Framebuffer abstraction!
    DW_WARN("Width: {0} , Height {1}", re.GetWidth() / 2, re.GetHeight());
    Dwarfworks::RenderCommand::SetViewport(re.GetWidth() / 2, 0,
                                           re.GetWidth() / 2, re.GetHeight());
    Dwarfworks::RenderCommand::SetScissor(re.GetWidth() / 2, 0,
                                          re.GetWidth() / 2, re.GetHeight());
  }
#endif

  // ...
  eventManager.Dispatch<Dwarfworks::KeyPressedEvent>([&](auto& ke) {
    switch (ke.GetKeyCode()) {
      case Dwarfworks::KeyCodes::ESCAPE: {
        DW_INFO("Pressed 'ESC'");
        break;
      }
      default:
        DW_TRACE("Pressed {0}", static_cast<char>(ke.GetKeyCode()));
        break;
    }
    return false;  // is blocking (true for non-blocking)
  });
}
