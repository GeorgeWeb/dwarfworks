#include "dwpch.h"

#include "LinuxInput.h"

#include "Dwarfworks/Core/Application/Application.h"

#include "GLFW/glfw3.h"

using namespace Dwarfworks;

Scope<Input> Input::s_Instance = CreateScope<LinuxInput>();

bool LinuxInput::IsKeyPressedImpl(int keycode) const
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().Get());
    auto state  = glfwGetKey(window, keycode);
    if (state == GLFW_PRESS || state == GLFW_REPEAT)
    {
        return true;
    }
    return false;
}

bool LinuxInput::IsMouseButtonPressedImpl(int button) const
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().Get());
    auto state  = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::GetMousePositionImpl() const
{
    auto   window = static_cast<GLFWwindow*>(Application::Get().GetWindow().Get());
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return std::make_pair(static_cast<float>(xPos), static_cast<float>(yPos));
}

float LinuxInput::GetMouseXImpl() const
{
    const auto [x, y] = GetMousePositionImpl();
    return x;
}

float LinuxInput::GetMouseYImpl() const
{
    const auto [x, y] = GetMousePositionImpl();
    return y;
}
