#include "OpenGLBuffer.h"
#include "OpenGLLoader.h"

namespace Papaya
{

static GLenum BufferTypeToGLEnum(BufferType type)
{
  switch (type)
  {
  case BufferType::Vertex:
  {
    return GL_ARRAY_BUFFER;
    break;
  }

  case BufferType::Index:
  {
    return GL_ELEMENT_ARRAY_BUFFER;
    break;
  }

  default: break;
  }

  return GL_ARRAY_BUFFER;
}

OpenGLBuffer::OpenGLBuffer(const void* vertices, uint32_t size, BufferType type)
{
  m_Type = BufferTypeToGLEnum(type);

  glGenBuffers(1, &m_RendererID);

  glBindBuffer(m_Type, m_RendererID);
  glBufferData(m_Type, size, vertices, GL_STATIC_DRAW);

  glBindBuffer(m_Type, 0);
}

OpenGLBuffer::~OpenGLBuffer()
{

}

void OpenGLBuffer::Bind()
{
  glBindBuffer(m_Type, m_RendererID);
}

void OpenGLBuffer::Unbind()
{
  glBindBuffer(m_Type, 0);
}

} // namespace Papaya
