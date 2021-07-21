#pragma once

#include <glm/glm.hpp>

namespace Papaya
{
  class Camera {
  public:
    Camera() = default;
    Camera(const glm::mat4& projection);
    virtual ~Camera() = default;

    // Can be overriden by child classes
    virtual void SetProjectionMatrix(const glm::mat4& projection) { m_Projection = projection; }
    virtual const glm::mat4& GetViewProjectionMatrix() const { return m_Projection;  } 

    const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
  protected:
    glm::mat4 m_Projection = glm::mat4(1.0f);
  };
} // namespace Papaya