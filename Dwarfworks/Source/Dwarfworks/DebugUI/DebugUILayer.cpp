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

void DebugUILayer::OnAttach() {
  // Setup ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  auto& io = ImGui::GetIO();
  static_cast<void>(io);
  // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  // Enable Gamepad Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // Enable Multi-Viewport / Platform Windows
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

  // Setup ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // When Viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones
  auto& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  auto& app = Application::Get();
  auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

void DebugUILayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void DebugUILayer::OnDebugUIRender() {
  // static bool show = true;
  // ImGui::ShowDemoWindow(&show);
}

void DebugUILayer::Begin() const {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void DebugUILayer::End() const {
  auto& io = ImGui::GetIO();
  auto& app = Application::Get();
  const auto width = app.GetWindow().GetWidth();
  const auto height = app.GetWindow().GetHeight();
  io.DisplaySize = {static_cast<float>(width), static_cast<float>(height)};

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    auto backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

}  // namespace Dwarfworks
