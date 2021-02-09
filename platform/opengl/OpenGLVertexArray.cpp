#include "OpenGLVertexArray.h"
#include "OpenGLLoader.h"

namespace Papaya
{

OpenGLVertexArray::OpenGLVertexArray()
{
  glGenVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
  // TODO: Add deletion
}

void OpenGLVertexArray::SetVertexBuffer(const Ref<Buffer>& buffer)
{
  glBindVertexArray(m_RendererID); // OpenGL sucks
  buffer->Bind();
}

void OpenGLVertexArray::SetIndexBuffer(const Ref<Buffer>& buffer)
{
  m_IndexBuffer = buffer;
}

void OpenGLVertexArray::Bind()
{
  glBindVertexArray(m_RendererID);
  m_IndexBuffer->Bind();
}

void OpenGLVertexArray::Unbind()
{
  glBindVertexArray(0);
}

} // namespace Papaya
