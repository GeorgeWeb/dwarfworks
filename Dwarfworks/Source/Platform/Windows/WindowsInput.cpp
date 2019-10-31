#include "dwpch.h"

#include "WindowsInput.h"

#include "Dwarfworks/Core/Application/Application.h"

#include <GLFW/glfw3.h>

namespace Dwarfworks {

Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

bool WindowsInput::IsKeyPressedImpl(int keycode) const {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetKey(window, keycode);
  if (state == GLFW_PRESS || state == GLFW_REPEAT) {
    return true;
  }
  return false;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) const {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl() const {
  auto window = static_cast<GLFWwindow*>(
      Application::Get().GetWindow().GetNativeWindow());
  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  return std::make_pair(static_cast<float>(xPos), static_cast<float>(yPos));
}

float WindowsInput::GetMouseXImpl() const {
  const auto [x, y] = GetMousePositionImpl();
  return x;
}

float WindowsInput::GetMouseYImpl() const {
  const auto [x, y] = GetMousePositionImpl();
  return y;
}

}  // namespace Dwarfworks
