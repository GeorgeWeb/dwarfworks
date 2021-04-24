#ifndef GRAPHICS_CAMERA_H_
#define GRAPHICS_CAMERA_H_

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Math/Math.h"

namespace Dwarfworks
{
// 2D Orthographic Camera
class ENGINE_API OrthographicCamera
{
  public:
    // Constructor that takes (rectangle) bounds (for orthographic matrix)
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);

    inline const glm::vec3& GetPosition() const { return m_Position; }
    inline void             SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

    // rotate along the 'Z' axis
    inline float GetRotation() const { return m_Rotation; }
    inline void  SetRotation(float rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

  public:
    // TODO: Hook this up with the event system to recalculate
    // the matrices when needed (recalculate when receive event)
    // void OnUpdate();

  private:
    // Temporary, until hooked with the events system
    void RecalculateViewMatrix();

  private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    // transformation of the camera
    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    float     m_Rotation = 0.0f; // rotate over the 'Z' axis (2D)
};

// 3D Perspective Camera
class ENGINE_API OrbitalCamera
{
  public:
};

} // namespace Dwarfworks

#endif // GRAPHICS_CAMERA_H_
