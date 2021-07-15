#pragma once

#include <glm/glm.hpp>

namespace Papaya
{

  enum class CameraType {
    Orthographic,
    Perspective
  };

  class Camera {
  public:
    Camera() = default;
    Camera(const glm::mat4& projection);
    virtual ~Camera() = default;

    void SetProjectionMatrix(const glm::mat4& projection);
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }
    const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position)
    {
      m_Position = position;
      RecalculateViewMatrix();
    }

    float GetRotation() const { return m_Rotation; }
    void SetRotation(float rotation)
    {
      m_Rotation = rotation;
      RecalculateViewMatrix();
    }

  protected:
    void RecalculateViewMatrix();
    void RecalculateViewProjectionMatrix();
  protected:
    glm::mat4 m_View = glm::mat4(1.0f);
    glm::mat4 m_Projection = glm::mat4(1.0f);
    glm::mat4 m_ViewProjection = glm::mat4(1.0f);

    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_Rotation = 0.0f;
  };

} // namespace Papaya