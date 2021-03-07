#pragma once

#include "main/renderer/Buffer.h"

namespace Papaya
{

  class OpenGLVertexArray
  {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    // This function can be called multiple times to add another buffer.
    void SetVertexBuffer(const Ref<Buffer> &buffer);
    void SetIndexBuffer(const Ref<Buffer> &buffer);

    void Bind();
    void Unbind();

  private:
    unsigned int m_RendererID;
    Ref<Buffer> m_IndexBuffer;
  };

} // namespace Papaya