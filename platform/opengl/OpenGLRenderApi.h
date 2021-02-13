#ifndef OpenGLRenderApi_h
#define OpenGLRenderApi_h

#include "main/renderer/RenderApi.h"

namespace Papaya
{

  class OpenGLRenderApi : public RenderApi
  {
  public:
    OpenGLRenderApi();
    virtual ~OpenGLRenderApi();

    void ClearColor(float r, float b, float g, float a);
    void Clear();

    void DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                     const Ref<PipelineState> &pipelineState,
                     const Ref<Buffer> &indexBuffer);
  };

} // namespace Papaya

#endif /* end of include guard: OpenGLRenderApi_h */