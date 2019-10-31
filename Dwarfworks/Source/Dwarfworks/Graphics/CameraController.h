#ifndef GRAPHICS_CAMERA_CONTROLLER_H_
#define GRAPHICS_CAMERA_CONTROLLER_H_

#include "Dwarfworks/Core/Timestep.h"
#include "Dwarfworks/Events/ApplicationEvent.h"
#include "Dwarfworks/Events/MouseEvent.h"
#include "Dwarfworks/Graphics/Camera.h"

namespace Dwarfworks {

class OrthographicCameraController {
 public:
  OrthographicCameraController(float aspectRatio, bool canRotate = false);

  inline OrthographicCamera& GetCamera() { return m_Camera; }
  inline const OrthographicCamera& GetCamera() const { return m_Camera; }

  inline float GetZoomLevel() const { return m_ZoomLevel; }
  inline void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

  void OnUpdate(Timestep deltaTime);
  void OnEvent(Event& event);

 private:
  bool OnMouseScrolled(MouseScrolledEvent& mouseEvent);
  bool OnWindowResized(WindowResizeEvent& windowEvent);

 private:
  float m_AspectRatio;
  float m_ZoomLevel = 1.0f;
  OrthographicCamera m_Camera;

  bool m_CanRotate;

  glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
  float m_CameraRotation = 0.0f;  // degrees, in anti-clockwise direction

  // default translation speed
  float m_CameraTranslationSpeed = 1.0f;
  // default rotation speed
  float m_CameraRotationSpeed = glm::degrees(glm::half_pi<float>());

  // default zoom speed
  float m_ZoomSpeed = 0.25f;
};

// 3D Perspective Camera Controller
// TODO: Implement!

}  // namespace Dwarfworks

#endif  // GRAPHICS_CAMERA_CONTROLLER_H_
