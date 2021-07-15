#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

  SceneCamera::SceneCamera(float left, float right, float bottom, float top)
  {
    m_Projection = glm::ortho(left, right, bottom, top);
  }

  SceneCamera::~SceneCamera()
  {
  }

  void SceneCamera::SetOrthographic(float left, float right, float bottom, float top)
  {
    SetProjectionMatrix(glm::ortho(left, right, bottom, top));
  }

} // namespace Papaya