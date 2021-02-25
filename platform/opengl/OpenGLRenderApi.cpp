#include "OpenGLRenderApi.h"
#include "OpenGLLoader.h"

#include "OpenGLVertexArray.h"
#include "OpenGLVertexArrayCache.h"

namespace Papaya
{

  OpenGLRenderApi::OpenGLRenderApi()
  {
  }

  OpenGLRenderApi::~OpenGLRenderApi()
  {
  }

  void OpenGLRenderApi::SetViewport(float x, float y, float w, float h)
  {
    glViewport(static_cast<GLint>(x),
               static_cast<GLint>(y),
               static_cast<GLsizei>(w),
               static_cast<GLsizei>(h));
  }

  void OpenGLRenderApi::ClearColor(float r, float g, float b, float a)
  {
    glClearColor(r, g, b, a);
  }

  void OpenGLRenderApi::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRenderApi::DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                                    const Ref<PipelineState> &pipelineState,
                                    const Ref<Buffer> &indexBuffer)
  {
    Ref<OpenGLVertexArray> vertexArray = OpenGLVertexArrayCache::GetVertexArray(vertexBuffers,
                                                                                pipelineState,
                                                                                indexBuffer);

    vertexArray->Bind();
    pipelineState->Bind();
    int count = indexBuffer->GetSize() / sizeof(uint32_t);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
  }

} // namespace Papaya
