#pragma once

#include "main/core/Input.h"
#include "main/core/Timestep.h"
#include "main/renderer/Camera.h"

namespace Papaya
{

  class EditorCamera : public Camera
  {
  public:
    EditorCamera(float fov = 70, float near = 0.1f, float far = 1000.0f);
    virtual ~EditorCamera();

    void OnUpdate(Timestep ts, bool running = false);
    void SetFOV(float fov);
    void SetNear(float nearLimit);
    void SetFar(float farLimit);
    void SetViewportSize(uint32_t width, uint32_t height);

  private:
    void RecalculateProjectionMatrix();
  private:
    float m_FOV, m_Near, m_Far;
    float m_Width = 1.0f, m_Height = 1.0f;
    float m_PixelsPerUnit = 300.0f;
  };

} // namespace Papaya