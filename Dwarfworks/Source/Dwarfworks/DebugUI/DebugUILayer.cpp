#include "dwpch.h"

#include "DebugUILayer.h"

#include "imgui.h"

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "Dwarfworks/Core/Application/Application.h"

// TEMPORARY UNTIL Drawrfworks::Input is setup
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Dwarfworks {

DebugUILayer::DebugUILayer() : Layer("DebugUILayer") {}

DebugUILayer::~DebugUILayer() {
  // ...
}

void DebugUILayer::OnAttach() {
  /* auto context = */
  ImGui::CreateContext();
  // ImGui::SetCurrentContext(context);
  ImGui::StyleColorsDark();

  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  // TEMPORARY UNTIL Drawrfworks::Input is setup
  // Keyboard mapping. ImGui will use those indices to peek into the
  // io.KeysDown[] array.
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  ImGui_ImplOpenGL3_Init("#version 410");
}

void DebugUILayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void DebugUILayer::OnUpdate() {
  ImGuiIO& io = ImGui::GetIO();
  Application& app = Application::Get();
  const auto width = static_cast<float>(app.GetWindow().GetWidth());
  const auto height = static_cast<float>(app.GetWindow().GetHeight());
  io.DisplaySize = ImVec2(width, height);

  float time = static_cast<float>(glfwGetTime());
  io.DeltaTime = m_Time > 0.0f ? time - m_Time : 1.0f / 60.0f;
  m_Time = time;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool showDemoWindow = true;
  ImGui::ShowDemoWindow();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugUILayer::OnEvent(Event& event) {
  // listen for event
  EventManager eventManager(event);

  // Dispatch events
  // ---------------

  ImGuiIO& io = ImGui::GetIO();
  eventManager.Dispatch<MouseButtonPressedEvent>([&io](auto& e) {
    io.MouseDown[e.GetMouseButton()] = true;
    // Temporary:
    // Just return false because we're not doing button clicked check
    // Future:
    // Detect whether a button was actually clicked and the mouse is
    // over the button, we don't want other layers to get it -> return false
    // As a consequence:
    // This same logic applies to the rest of ImGui event handling
    // implemenetation for the Debug UI (for now!)
    return false;
  });

  eventManager.Dispatch<MouseButtonReleasedEvent>([&io](auto& e) {
    io.MouseDown[e.GetMouseButton()] = false;
    return false;  // see MouseButtonPressedEvent handling for explanation
  });

  eventManager.Dispatch<MouseMovedEvent>([&io](auto& e) {
    io.MousePos = ImVec2(e.GetX(), e.GetY());
    return false;  // see MouseButtonPressedEvent handling for explanation
  });

  eventManager.Dispatch<MouseScrolledEvent>([&io](auto& e) {
    io.MouseWheelH += e.GetXOffset();
    io.MouseWheel += e.GetYOffset();
    return false;  // see MouseButtonPressedEvent handling for explanation
  });

  eventManager.Dispatch<WindowResizeEvent>([&io](auto& e) {
    const auto width = e.GetWidth();
    const auto height = e.GetHeight();
    io.DisplaySize = ImVec2((float)width, (float)height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);  // TODO: handle later
    glViewport(0, 0, width, height);  // TODO: fix when we have proper renderer
    return false;  // see MouseButtonPressedEvent handling for explanation
  });

  eventManager.Dispatch<KeyPressedEvent>([&io](auto& e) {
    io.KeysDown[e.GetKeyCode()] = true;

    // Modifier keys support (for now GLFW_KEYCODE, later with our Input system)
    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                 io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift =
        io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt =
        io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper =
        io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    return false;  // see MouseButtonPressedEvent handling for explanation
  });

  eventManager.Dispatch<KeyReleasedEvent>([&io](auto& e) {
    io.KeysDown[e.GetKeyCode()] = false;
    return false;  // see MouseButtonPressedEvent handling for explanation
  });

  eventManager.Dispatch<KeyTypedEvent>([&io](auto& e) {
    if (const auto keycode = e.GetKeyCode(); keycode > 0 && keycode < 0x10000) {
      io.AddInputCharacter(static_cast<unsigned short>(keycode));
    }
    return false;  // see MouseButtonPressedEvent handling for explanation
  });
}

[[maybe_unused]] void DebugUILayer::Begin() const {
  // TODO
}

[[maybe_unused]] void DebugUILayer::End() const {
  // TODO
}

}  // namespace Dwarfworks
