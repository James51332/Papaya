#ifndef OpenGLVertexArray_h
#define OpenGLVertexArray_h

#include "main/renderer/Buffer.h"

namespace Papaya
{

class OpenGLVertexArray
{
public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();

  void SetVertexBuffer(const Ref<Buffer>& buffer);
  void SetIndexBuffer(const Ref<Buffer>& buffer);

  void Bind();
  void Unbind();

private:
  unsigned int m_RendererID;
  Ref<Buffer> m_IndexBuffer;
};

} // namespace Papaya

#endif /* end of include guard: OpenGLVertexArray_h */