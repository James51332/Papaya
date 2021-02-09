#include "VertexArray.h"

#include "platform/opengl/OpenGLVertexArray.h"

namespace Papaya
{

Ref<VertexArray> VertexArray::Create()
{
  return CreateRef<OpenGLVertexArray>();
}

VertexArray::~VertexArray()
{

}

} // namespace Papaya
