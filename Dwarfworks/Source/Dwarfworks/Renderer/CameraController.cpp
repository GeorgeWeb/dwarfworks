// begin PCH
#include "dwpch.h"
// end PCH

#include "CameraController.h"
#include "Dwarfworks/Core/Input/Input.h"
#include "Dwarfworks/Core/Input/KeyCodeDefinitions.h"
#include "Dwarfworks/Core/Input/MouseButtonDefinitions.h"
#include "Dwarfworks/Event/EventDispatcher.h"
#include "Dwarfworks/Math/Math.h"

using namespace Dwarfworks;

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canRotate)
    : m_AspectRatio(aspectRatio),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
      m_CanRotate(canRotate)
{
}

void OrthographicCameraController::OnUpdate(Timestep deltaTime)
{
    // horizontal movement
    if (Input::IsKeyPressed(KeyCode::A))
    {
        m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
    }
    else if (Input::IsKeyPressed(KeyCode::D))
    {
        m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
    }
    // vertical movement
    if (Input::IsKeyPressed(KeyCode::W))
    {
        m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
    }
    else if (Input::IsKeyPressed(KeyCode::S))
    {
        m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
        m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltaTime;
    }

    // rotation (z-axis)
    if (m_CanRotate)
    {
        if (Input::IsKeyPressed(KeyCode::Q))
            m_CameraRotation += m_CameraRotationSpeed * deltaTime;
        if (Input::IsKeyPressed(KeyCode::E))
            m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

        if (m_CameraRotation > glm::degrees(glm::pi<float>()))        // > 180
            m_CameraRotation -= glm::degrees(glm::two_pi<float>());   // -= 360
        else if (m_CameraRotation <= -glm::degrees(glm::pi<float>())) // <= -180
            m_CameraRotation += glm::degrees(glm::two_pi<float>());   // += 360

        // rotate
        m_Camera.SetRotation(m_CameraRotation);
    }

    // translate
    m_Camera.SetPosition(m_CameraPosition);
    m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event& event)
{
    EventDispatcher eventDispatcher(event);
    eventDispatcher.Dispatch<MouseScrolledEvent>(BIND_MEMBER(OrthographicCameraController::OnMouseScrolled));
    eventDispatcher.Dispatch<WindowResizeEvent>(BIND_MEMBER(OrthographicCameraController::OnWindowResize));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
{
    m_ZoomLevel -= event.GetYOffset() * m_ZoomSpeed;
    m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomSpeed);

    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

    return false;
}

bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& event)
{
    const auto width  = event.GetWidth();
    const auto height = event.GetHeight();

    m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);

    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

    return false;
}
