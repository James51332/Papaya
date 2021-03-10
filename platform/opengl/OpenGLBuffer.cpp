#include "OpenGLBuffer.h"
#include "OpenGLLoader.h"

#include "main/core/Log.h"

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

    default:
      break;
    }

    return GL_ARRAY_BUFFER;
  }

  static GLenum BufferUsageToGLEnum(BufferUsage usage)
  {
    switch (usage)
    {
    case BufferUsage::Immutable:
    {
      return GL_STATIC_DRAW;
      break;
    }

    case BufferUsage::Dynamic:
    {
      return GL_DYNAMIC_DRAW;
      break;
    }

    case BufferUsage::Stream:
    {
      return GL_STREAM_DRAW;
      break;
    }

    default:
      break;
    }

    return GL_STATIC_DRAW;
  }

  // Start at 1000 to prevent same id's at BufferLayout
  int OpenGLBuffer::m_CurID = 1000;

  OpenGLBuffer::OpenGLBuffer(const void *data, uint32_t size, BufferType type, BufferUsage usage)
  {
    m_UniqueID = m_CurID;
    m_CurID++;

    glGenBuffers(1, &m_RendererID);
    Reset(data, size, type, usage);
  }

  OpenGLBuffer::OpenGLBuffer()
  {
    m_Size = 0;
    m_UniqueID = m_CurID;
    m_CurID++;

    glGenBuffers(1, &m_RendererID);
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

  void OpenGLBuffer::SetData(const void *data, uint32_t size)
  {
    PAPAYA_ASSERT((m_Size != 0), "SetData() called before buffer initialization! Try calling Buffer::Reset()");

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }

  void OpenGLBuffer::Reset(const void *data, uint32_t size, BufferType type, BufferUsage usage)
  {
    m_Type = BufferTypeToGLEnum(type);
    m_Usage = BufferUsageToGLEnum(usage);
    m_Size = size;

    glBindBuffer(m_Type, m_RendererID);
    glBufferData(m_Type, size, data, m_Usage);

    glBindBuffer(m_Type, 0);
  }

} // namespace Papaya
