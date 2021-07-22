#pragma once

#include "OpenGLVertexArray.h"
#include "OpenGLPipelineState.h"

#include "main/renderer/Buffer.h"
#include "main/renderer/BufferLayout.h"

namespace Papaya
{

  class OpenGLVertexArrayCache
  {
  public:
    ~OpenGLVertexArrayCache();

    static Ref<OpenGLVertexArray> GetVertexArray(const std::vector<Ref<Buffer>> &vertexBuffers,
                                                 const Ref<PipelineState> &pipelineState,
                                                 const Ref<Buffer> &indexBuffer);

  private:
    static std::unordered_map<std::size_t, Ref<OpenGLVertexArray>> s_Cache;
  };

} // namespace Papaya