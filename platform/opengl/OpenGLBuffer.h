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

  uint32_t GetSize() const { return m_Size; }

  int GetUniqueID() const { return m_UniqueID; }

private:
  unsigned int m_RendererID;
  uint32_t m_Size;
  int m_Type;
  int m_UniqueID;

  static int m_CurID;
};

} // namespace Papaya


#endif /* end of include guard: OpenGLBuffer_h */