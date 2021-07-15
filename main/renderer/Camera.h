#pragma once

#include <glm/glm.hpp>

namespace Papaya
{

  class Camera {
  public:
    Camera() = default;
    Camera(const glm::mat4& projection);
    ~Camera() = default;

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

  private:
    void RecalculateViewMatrix();

  protected:
    glm::mat4 m_View;
    glm::mat4 m_Projection;
    glm::mat4 m_ViewProjection;

    glm::vec3 m_Position;
    float m_Rotation;
  };

} // namespace Papaya