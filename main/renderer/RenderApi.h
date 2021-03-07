#pragma once

#include "Buffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "PipelineState.h"

namespace Papaya
{

  class RenderApi
  {
  public:
    enum class API
    { // TODO: I don't know if we'll implement all of these but these are just the list of potential candidates
      None,
      OpenGL,
      DirectX,
      Metal,
      Vulkan,
    };

  public:
    static Scope<RenderApi> Create();
    virtual ~RenderApi();

    virtual void SetViewport(float x, float y, float w, float h) = 0;

    virtual void ClearColor(float r, float g, float b, float a) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                             const Ref<PipelineState>& pipelineState,
                             const Ref<Buffer> &indexBuffer) = 0;
  };

} // namespace Papaya