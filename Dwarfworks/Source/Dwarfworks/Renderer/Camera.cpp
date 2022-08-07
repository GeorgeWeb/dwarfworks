// begin PCH
#include "dwpch.h"
// end PCH

#include "Camera.h"
#include "glm/fwd.hpp"

using namespace Dwarfworks;

static constexpr float s_NearPlane = -1.0f;
static constexpr float s_FarPlane  = 1.0f;

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : Camera(glm::ortho(left, right, bottom, top, s_NearPlane, s_FarPlane))
{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix     = glm::ortho(left, right, bottom, top, s_NearPlane, s_FarPlane);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    // create transform matrix (rotated by 'Z' axis)
    glm::mat4 transform =
        glm::translate(glm::identity<glm::mat4>(), m_Position) *
        glm::rotate(glm::identity<glm::mat4>(), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    m_ViewMatrix = glm::inverse(transform);
    // Note: Using OpenGL matrix multiplication order
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
