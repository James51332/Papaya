#include "EditorCamera.h"

#include "main/core/Input.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Papaya
{

  EditorCamera::EditorCamera(float fov, float aspect, float nearClip, float farClip)
    : m_FOV(fov), m_Aspect(aspect), m_Near(nearClip), m_Far(farClip), Camera(glm::perspective(glm::radians(fov), aspect, nearClip, farClip))
  {
    m_ViewProjection = m_Projection;
  }

  EditorCamera::~EditorCamera()
  {
  }

  void EditorCamera::OnUpdate(Timestep ts)
  {

  }

  void EditorCamera::RecalculateProjectionMatrix()
  {
    m_Projection = glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
    m_ViewProjection = m_Projection * m_View;
  }

  void EditorCamera::RecalculateViewMatrix()
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
      * glm::toMat4(glm::quat(m_Rotation));

    m_View = glm::inverse(transform);
    m_ViewProjection = m_Projection * m_View;
  }

} // namespace Papaya