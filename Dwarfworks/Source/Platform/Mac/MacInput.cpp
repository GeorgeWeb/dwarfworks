// begin PCH
#include "dwpch.h"
// end PCH

#include "MacInput.h"

#include "Dwarfworks/Core/Application/Application.h"

#include "GLFW/glfw3.h"

using namespace Dwarfworks;

Scope<Input> Input::s_Instance = CreateScope<MacInput>();

bool MacInput::IsKeyPressedImpl(int keycode) const
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().Get());
    auto state  = glfwGetKey(window, keycode);
    if (state == GLFW_PRESS || state == GLFW_REPEAT)
    {
        return true;
    }
    return false;
}

bool MacInput::IsMouseButtonPressedImpl(int button) const
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().Get());
    auto state  = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> MacInput::GetMousePositionImpl() const
{
    auto   window = static_cast<GLFWwindow*>(Application::Get().GetWindow().Get());
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return std::make_pair(static_cast<float>(x), static_cast<float>(y));
}

float MacInput::GetMouseXImpl() const
{
    const auto [x, y] = GetMousePositionImpl();
    return x;
}

float MacInput::GetMouseYImpl() const
{
    const auto [x, y] = GetMousePositionImpl();
    return y;
}
