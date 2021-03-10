#pragma once

#include "main/renderer/RenderApi.h"

namespace Papaya
{

  class OpenGLRenderApi : public RenderApi
  {
  public:
    OpenGLRenderApi();
    virtual ~OpenGLRenderApi();

    void OnInit();
    void OnTerminate();

    void SetViewport(float x, float y, float w, float h);

    void ClearColor(float r, float b, float g, float a);
    void Clear();

    void DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                     const Ref<PipelineState> &pipelineState,
                     const Ref<Buffer> &indexBuffer,
                     uint32_t indexSize,
                     uint32_t indexOffset);
  };

} // namespace Papaya