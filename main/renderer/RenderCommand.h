#pragma once

#include "Buffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "RenderApi.h"

#include "main/utils/Memory.h"

namespace Papaya
{

  class RenderCommand
  {
  public:
    static void OnInit() {}
    static void OnTerminate() {}

    static void SetViewport(float x, float y, float w, float h)
    {
        s_Api->SetViewport(x, y, w, h);
    }

    static void ClearColor(float r, float g, float b, float a = 1.0f)
    {
      s_Api->ClearColor(r, g, b, a);
    }

    static void Clear()
    {
      s_Api->Clear();
    }

    static void DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                            const Ref<PipelineState> pipelineState,
                            const Ref<Buffer> &indexBuffer)

    {
        s_Api->DrawIndexed(vertexBuffers, pipelineState , indexBuffer);
    }

  private:
    static Scope<RenderApi> s_Api;
  };

} // namespace Papaya