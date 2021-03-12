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

  void OpenGLRenderApi::OnInit()
  {
    // glEnable(GL_BLEND);
    // glBlendEquation(GL_FUNC_ADD);
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    // glDisable(GL_CULL_FACE);
    // glDisable(GL_DEPTH_TEST);
    // glEnable(GL_SCISSOR_TEST);
    // glDisable(GL_STENCIL_TEST);
    // glDisable(GL_PRIMITIVE_RESTART);
    // glDisable(GL_DITHER);
  }

  void OpenGLRenderApi::OnTerminate()
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
                                    const Ref<Buffer> &indexBuffer,
                                    uint32_t indexSize,
                                    uint32_t indexOffset,
                                    uint32_t elemCount)
  {
    Ref<OpenGLVertexArray> vertexArray = OpenGLVertexArrayCache::GetVertexArray(vertexBuffers,
                                                                                pipelineState,
                                                                                indexBuffer);

    vertexArray->Bind();
    pipelineState->Bind();
    int count = elemCount == 0 ? indexBuffer->GetSize() / indexSize : elemCount;
    glDrawElements(GL_TRIANGLES, count, indexSize == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (GLvoid *)(long long)indexOffset);
  }

} // namespace Papaya
