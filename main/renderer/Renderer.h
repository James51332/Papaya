#ifndef Renderer_h
#define Renderer_h

#include "main/utils/Memory.h"

#include "RenderApi.h"
#include "Buffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "PipelineState.h"

#include <vector>

namespace Papaya
{

  class Renderer
  {
  public:
    static void OnInit();
    static void OnTerminate();

    static void Begin();

    static void Submit(const std::vector<Ref<Buffer>> &vertexBuffers,
                       const Ref<PipelineState> pipelineState,
                       const Ref<Buffer> &indexBuffer);

    static void End();

    static RenderApi::API GetApi() { return s_Api; }

  private:
    static RenderApi::API s_Api;
  };

} // namespace Papaya

#endif /* end of include guard: Renderer_h */