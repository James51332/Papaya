#ifndef Renderer_h
#define Renderer_h

#include "main/utils/Memory.h"

#include "RenderApi.h"
#include "Buffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "PipelineState.h"
#include "Camera.h"

#include <vector>
#include <glm/matrix.hpp>

namespace Papaya
{

  class Renderer
  {
  public:
    static void OnInit();
    static void OnTerminate();

    static void Begin(const OrthographicCamera &camera);

    static void Submit(const std::vector<Ref<Buffer>> &vertexBuffers,
                       const Ref<PipelineState> pipelineState,
                       const Ref<Buffer> &indexBuffer);

    static void Submit(const Ref<Buffer> &vertexBuffer,
                       const Ref<PipelineState> pipelineState,
                       const Ref<Buffer> &indexBuffer);

    static void End();

    static RenderApi::API GetApi() { return s_Api; }

  private:
    static RenderApi::API s_Api;
    static glm::mat4 s_ViewProjection;
  };

} // namespace Papaya

#endif /* end of include guard: Renderer_h */