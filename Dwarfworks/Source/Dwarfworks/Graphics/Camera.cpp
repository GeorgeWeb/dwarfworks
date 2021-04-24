// begin PCH
#include "dwpch.h"
// end PCH

#include "Camera.h"

namespace Dwarfworks
{
static constexpr float near = -1.0f;
static constexpr float far  = 1.0f;

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, near, far)), m_ViewMatrix(1.0f)
{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix     = glm::ortho(left, right, bottom, top, near, far);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    // create transform matrix (rotated by 'z' axis)
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(transform);
    // Note: Using OpenGL matrix multiplication order
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

} // namespace Dwarfworks
