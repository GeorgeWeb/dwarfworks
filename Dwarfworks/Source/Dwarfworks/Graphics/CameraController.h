#ifndef GRAPHICS_CAMERA_CONTROLLER_H_
#define GRAPHICS_CAMERA_CONTROLLER_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Core/Timestep.h"
#include "Dwarfworks/Events/ApplicationEvent.h"
#include "Dwarfworks/Events/MouseEvent.h"
#include "Dwarfworks/Graphics/Camera.h"

namespace Dwarfworks {

class DW_API OrthographicCameraController {
 public:
  OrthographicCameraController(float aspectRatio, bool canRotate = false);

  OrthographicCamera& GetCamera() { return m_Camera; }
  const OrthographicCamera& GetCamera() const { return m_Camera; }

  inline float GetZoomLevel() const { return m_ZoomLevel; }
  inline void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

  void OnUpdate(Timestep deltaTime);
  void OnEvent(Event& event);

 private:
  // bool OnMouseMoved(MouseMovedEvent& mouseEvent);
  bool OnMouseScrolled(MouseScrolledEvent& event);
  bool OnWindowResize(WindowResizeEvent& event);

 private:
  float m_AspectRatio;
  float m_ZoomLevel = 1.0f;
  OrthographicCamera m_Camera;

  bool m_CanRotate;

  glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
  // rotate angle - degrees in anti-clockwise direction (OpenGL)
  float m_CameraRotation = 0.0f;

  // default translation speed
  float m_CameraTranslationSpeed = 1.0f;
  // default rotation speed
  float m_CameraRotationSpeed = glm::degrees(glm::half_pi<float>());

  // default zoom speed
  float m_ZoomSpeed = 0.25f;
};

// TODO: 3D Perspective Camera Controller
class DW_API OrbitalCameraController {
 public:
  inline OrbitalCamera& GetCamera() { return m_Camera; }
  inline const OrbitalCamera& GetCamera() const { return m_Camera; }

 private:
  OrbitalCamera m_Camera;
};

}  // namespace Dwarfworks

#endif  // GRAPHICS_CAMERA_CONTROLLER_H_
