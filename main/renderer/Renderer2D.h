#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"

namespace Papaya
{

  class Renderer;

  // Renderer2D is a batched renderer
  class Renderer2D
  {
    friend class Renderer;

  public:
    static void BeginScene(const OrthographicCamera &camera);
    static void EndScene();

    static void DrawQuad(const glm::mat4 &transform = glm::mat4(1.0f), const glm::vec4 &color = glm::vec4(1.0f));

  private:
    static void StartBatch();
    static void Flush();

    static void OnInit();
    static void OnTerminate();
  };

} // namespace Papaya
