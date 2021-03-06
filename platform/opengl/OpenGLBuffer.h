#pragma once

#include "main/renderer/Buffer.h"

namespace Papaya
{

  class OpenGLBuffer : public Buffer
  {
  public:
    OpenGLBuffer(const void *data, uint32_t size, BufferType type, BufferUsage usage);
    OpenGLBuffer();
    virtual ~OpenGLBuffer();

    void Bind();
    void Unbind();

    void SetData(const void *data, uint32_t size);
    void Reset(const void* data, uint32_t size, BufferType type, BufferUsage usage);

    uint32_t GetSize() const { return m_Size; }

    int GetUniqueID() const { return m_UniqueID; }

  private:
    unsigned int m_RendererID;
    uint32_t m_Size;
    int m_Type;
    int m_Usage;
    int m_UniqueID;

    static int m_CurID;
  };

} // namespace Papaya