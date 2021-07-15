#include "EditorCamera.h"

#include "main/core/Log.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

  EditorCamera::EditorCamera(float fov, float nearLimit, float farLimit)
    : m_FOV(fov), m_Near(nearLimit), m_Far(farLimit), Camera(glm::perspective(glm::radians(fov), 1.77f, nearLimit, farLimit))
  {
  }

  EditorCamera::~EditorCamera()
  {
  }

  void EditorCamera::OnUpdate(Timestep ts, bool running)
  {
    if (running)
      return;

    // TODO: Movement in 3D
    if (Input::KeyDown(Papaya::KeyW))
     SetPosition(m_Position + glm::vec3(0.0f, 4.0f * ts, 0.0f));
    if (Input::KeyDown(Papaya::KeyS))
      SetPosition(m_Position - glm::vec3(0.0f, 4.0f * ts, 0.0f));
    if (Input::KeyDown(Papaya::KeyD))
      SetPosition(m_Position + glm::vec3(4.0f * ts, 0.0f, 0.0f));
    if (Input::KeyDown(Papaya::KeyA))
      SetPosition(m_Position - glm::vec3(4.0f * ts, 0.0f, 0.0f));
    if (Input::KeyDown(Papaya::KeyLeft))
      SetRotation(m_Rotation - 200.0f * static_cast<float>(ts));
    if (Input::KeyDown(Papaya::KeyRight))
      SetRotation(m_Rotation + 200.0f * static_cast<float>(ts));

    RecalculateViewMatrix();
  }

  void EditorCamera::SetFOV(float fov)
  {
    m_FOV = fov;
    RecalculateProjectionMatrix();
  }

  void EditorCamera::SetNear(float nearLimit)
  {
    m_Near = nearLimit;
    RecalculateProjectionMatrix();
  }

  void EditorCamera::SetFar(float farLimit)
  {
    m_Far = farLimit;
    RecalculateProjectionMatrix();
  }


  void EditorCamera::SetViewportSize(uint32_t width, uint32_t height)
  {
    m_Width = static_cast<float>(width) / m_PixelsPerUnit;
    m_Height = static_cast<float>(height) / m_PixelsPerUnit;
    RecalculateProjectionMatrix();
  }

  void EditorCamera::RecalculateProjectionMatrix()
  {
    float aspect = m_Width / m_Height;
    SetProjectionMatrix(glm::perspective(m_FOV, aspect > 0 ? aspect : 1, m_Near, m_Far));
  }

} // namespace Papaya