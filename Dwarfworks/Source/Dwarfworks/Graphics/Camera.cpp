// begin PCH
#include "dwpch.h"
// end PCH

#include "Camera.h"

namespace Dwarfworks {

OrthographicCamera::OrthographicCamera(glm::mat4 projectionMatrix,
                                       glm::mat4 viewMatrix)
    : m_ViewProjection(projectionMatrix, viewMatrix) {}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top, float near, float far)
    : m_ViewProjection(glm::ortho(left, right, bottom, top, near, far),
                       glm::mat4(1.0f)) {}

void OrthographicCamera::RecalculateViewMatrix() {
  // create transform matrix (rotated by 'z' axis)
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
  transform = glm::rotate(transform, glm::radians(m_Rotation),
                          glm::vec3(0.0f, 0.0f, 1.0f));

  m_ViewProjection.ViewMatrix = glm::inverse(transform);
  m_ViewProjection.ViewProjectionMatrix = /* OpenGL matrix mul order: */
      m_ViewProjection.ProjectionMatrix * m_ViewProjection.ViewMatrix;
}

}  // namespace Dwarfworks
