#include "Buffer.h"

#include "platform/opengl/OpenGLBuffer.h"

namespace Papaya
{

Ref<Buffer> Buffer::Create(const void* vertices, uint32_t size, BufferType type)
{
  return CreateRef<OpenGLBuffer>(vertices, size, type);
}

Buffer::~Buffer() {

}

} // namespace Papaya
