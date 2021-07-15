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
    static void BeginScene(const Camera& camera);
    static void BeginScene(const Camera& camera, const glm::mat4& transform);
    static void EndScene();

    // These are the two base function all other public functions call
    static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
    static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

  private:
    static void StartBatch();
    static void Flush();

    static void OnInit();
    static void OnTerminate();
  };

} // namespace Papaya
