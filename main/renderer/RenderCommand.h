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
    static void OnInit() 
    {
      s_Api->OnInit();  
    }

    static void OnTerminate() 
    {
      s_Api->OnTerminate();
    }

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
      s_Api->DrawIndexed(vertexBuffers, pipelineState, indexBuffer, s_IndexSize, s_IndexOffset, s_ElementCount);
    }

    static void SetIndexSize(uint32_t size)
    {
      s_IndexSize = size;
    }

    static void SetIndexOffset(uint32_t offset)
    {
      s_IndexOffset = offset;
    }

    static void SetElementCount(uint32_t count)
    {
        s_ElementCount = count;
    }

  private:
    static Scope<RenderApi> s_Api;
    
    static uint32_t s_IndexSize;
    static uint32_t s_IndexOffset;
    static uint32_t s_ElementCount;
  };

} // namespace Papaya
