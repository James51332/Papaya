#pragma once

#include "main/renderer/Camera.h"

namespace Papaya {

  enum class CameraType {
    Orthographic,
    Perspective
  };

  class SceneCamera : public Camera
  {
  public:
    SceneCamera(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f);
    ~SceneCamera();

    void SetOrthographic(float left, float right, float bottom, float top);
    // TODO: Create an API for perspective cameras in the ecs

  private:
    CameraType m_CameraType = CameraType::Orthographic;
  };

} // namespace Papaya
