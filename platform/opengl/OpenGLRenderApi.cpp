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

void OpenGLRenderApi::ClearColor(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
}

void OpenGLRenderApi::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderApi::DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                                  const BufferLayout &layout,
                                  const Ref<Buffer> &indexBuffer,
                                  const Ref<Shader> &shader)
{
  Ref<OpenGLVertexArray> vertexArray = OpenGLVertexArrayCache::GetVertexArray(vertexBuffers,
                                                                              layout,
                                                                              indexBuffer);

  vertexArray->Bind();
  shader->Bind();
  int count = static_cast<float>(indexBuffer->GetSize()) / sizeof(uint32_t);
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

} // namespace Papaya
