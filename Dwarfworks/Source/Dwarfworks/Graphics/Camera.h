#ifndef GRAPHICS_CAMERA_H_
#define GRAPHICS_CAMERA_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks {

// 2D Orthographic Camera

struct ViewProjection {
  glm::mat4 ProjectionMatrix;
  glm::mat4 ViewMatrix;

  // cache of the view-projection matrix
  glm::mat4 ViewProjectionMatrix;

  // constructing the view-projection matrix
  // note: accepts that the view matrix is inversed by default
  ViewProjection(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
      : ProjectionMatrix{projectionMatrix},
        ViewMatrix{viewMatrix},
        ViewProjectionMatrix{ProjectionMatrix * ViewMatrix} {}
};

class DW_API OrthographicCamera {
 public:
  // TODO: Implement generic camera constructor
  OrthographicCamera(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
  // Constructor that takes (rectangle) bounds (for orthographic matrix)
  OrthographicCamera(float left, float right, float bottom, float top,
                     float near = -1.0f, float far = 1.0f);

  inline const glm::vec3& GetPosition() const { return m_Position; }
  inline void SetPosition(const glm::vec3& position) {
    m_Position = position;
    RecalculateViewMatrix();
  }

  // rotate along the 'Z' axis
  inline float GetRotation() const { return m_Rotation; }
  inline void SetRotation(float rotation) {
    m_Rotation = rotation;
    RecalculateViewMatrix();
  }

  inline const glm::mat4& GetProjectionMatrix() const {
    return m_ViewProjection.ProjectionMatrix;
  }
  inline const glm::mat4& GetViewMatrix() const {
    return m_ViewProjection.ViewMatrix;
  }
  inline const glm::mat4& GetViewProjectionMatrix() const {
    return m_ViewProjection.ViewProjectionMatrix;
  }

 public:
  // TODO: Hook this up with the event system to recalculate
  // the matrices when needed (recalculate when receive event)
  // void OnUpdate();

 private:
  // TEMPORARY!
  void RecalculateViewMatrix();

 private:
  ViewProjection m_ViewProjection;

  // transformation of the camera
  glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
  float m_Rotation = 0.0f;  // rotate over the 'Z' axis (2D)
};

// 3D Perspective Camera
// TODO: Implement!

}  // namespace Dwarfworks

#endif  // GRAPHICS_CAMERA_H_
