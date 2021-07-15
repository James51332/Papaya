#include "Camera.h"

#include "main/core/Log.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <iostream>

namespace Papaya
{

  Camera::Camera(const glm::mat4& projection)
    : m_Projection(projection), m_View(1.0f), m_Position(0.0f), m_Rotation(0.0f)
  {
    m_ViewProjection = m_Projection * m_View; // column major is backwards. First we translate, then we distort into 3d space.
  }

  void Camera::SetProjectionMatrix(const glm::mat4& projection)
  {
    m_Projection = projection;
    m_ViewProjection = m_Projection * m_View;
  }

  void Camera::RecalculateViewMatrix()
  {
    // First Rotate
    // Second Translate
    // Third Invert (TODO: Consider Taking Negative Positions instead of inverting)
    // Fourth Calculate ViewProjection

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation), glm::vec3(0, 0, 1));

    m_View = glm::inverse(transform);
    m_ViewProjection = m_Projection * m_View;
  }

  void Camera::RecalculateViewProjectionMatrix()
  {
    m_ViewProjection = m_Projection * m_View;
  }

} // namespace Papaya
