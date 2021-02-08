#ifndef OpenGLBuffer_h
#define OpenGLBuffer_h

#include "main/renderer/Buffer.h"

namespace Papaya
{

class OpenGLBuffer : public Buffer
{
public:
  OpenGLBuffer(const void* data, uint32_t size, BufferType type);
  virtual ~OpenGLBuffer();

  void Bind();
  void Unbind();

private:
  unsigned int m_RendererID;
  int m_Type;
};

} // namespace Papaya


#endif /* end of include guard: OpenGLBuffer_h */