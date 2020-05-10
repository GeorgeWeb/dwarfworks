// begin PCH
#include "dwpch.h"
// end PCH

#include "CameraController.h"
#include "Dwarfworks/Core/Input/Input.h"
#include "Dwarfworks/Core/Input/KeyCodes.h"
#include "Dwarfworks/Core/Input/MouseButtonCodes.h"
#include "Dwarfworks/Events/EventManager.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

OrthographicCameraController::OrthographicCameraController(float aspectRatio,
                                                           bool canRotate)
    : m_AspectRatio(aspectRatio),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
               -m_ZoomLevel, m_ZoomLevel),
      m_CanRotate(canRotate) {}

void OrthographicCameraController::OnUpdate(Timestep deltaTime) {
  // horizontal movement
  if (Input::IsKeyPressed(KeyCodes::A)) {
    m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
    m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
  } else if (Input::IsKeyPressed(KeyCodes::D)) {
    m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
    m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
  }
  // vertical movement
  if (Input::IsKeyPressed(KeyCodes::W)) {
    m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
    m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
  } else if (Input::IsKeyPressed(KeyCodes::S)) {
    m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
    m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) *
                          m_CameraTranslationSpeed * deltaTime;
  }

  // rotation (z-axis)
  if (m_CanRotate) {
    if (Input::IsKeyPressed(KeyCodes::Q))
      m_CameraRotation += m_CameraRotationSpeed * deltaTime;
    if (Input::IsKeyPressed(KeyCodes::E))
      m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

    if (m_CameraRotation > glm::degrees(glm::pi<float>()))         // > 180
      m_CameraRotation -= glm::degrees(glm::two_pi<float>());      // -= 360
    else if (m_CameraRotation <= -glm::degrees(glm::pi<float>()))  // <= -180
      m_CameraRotation += glm::degrees(glm::two_pi<float>());      // += 360

    // rotate
    m_Camera.SetRotation(m_CameraRotation);
  }

  // translate
  m_Camera.SetPosition(m_CameraPosition);
  m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event& event) {
  EventManager eventManager(event);
  eventManager.Dispatch<MouseScrolledEvent>(
      DW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
  // Note: Default resizing behaviour, refactor later.
  eventManager.Dispatch<WindowResizeEvent>(
      DW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
  m_ZoomLevel -= event.GetYOffset() * m_ZoomSpeed;
  m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomSpeed);

  m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                         m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                         m_ZoomLevel);

  return false;
}

bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& event) {
  const auto width = event.GetWidth();
  const auto height = event.GetHeight();

  m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);

  m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                         m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                         m_ZoomLevel);

  return false;
}

}  // namespace Dwarfworks
