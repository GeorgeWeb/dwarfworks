#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include "Dwarfworks/Core/Core.h"
#include "Dwarfworks/Math/Math.h"
#include "glm/fwd.hpp"
#include "glm/gtc/constants.hpp"

namespace Dwarfworks
{
// Barebones Camera abstraction
class ENGINE_API Camera
{
  public:
    explicit Camera(const glm::mat4& projectionMatrix) : m_ProjectionMatrix(projectionMatrix) {}
    virtual ~Camera() = default;

    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

  protected: // TODO(georgi): make 'private'
    glm::mat4 m_ProjectionMatrix;
};

// 2D Orthographic Camera
class ENGINE_API OrthographicCamera final : public Camera
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
    void         SetRotation(float rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    // TODO (georgi): Hook this up with the event system to recalculate
    // the matrices when needed (recalculate when receive event)
    // void OnUpdate();

  protected:
    // Temp. - until hooked with the events system
    void RecalculateViewMatrix();

  private:
    glm::mat4 m_ViewMatrix = glm::identity<glm::mat4>();
    glm::mat4 m_ViewProjectionMatrix;

    // TODO(georgi): These should not be part of the camera but a 'Transform' component
    glm::vec3 m_Position = glm::zero<glm::vec3>();
    float     m_Rotation = 0.0f; // rotate over the 'Z' axis (2D)
};

// 3D Perspective Camera
class ENGINE_API OrbitalCamera
{
  public:
};

} // namespace Dwarfworks

#endif // RENDERER_CAMERA_H
