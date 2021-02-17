#include "Buffer.h"

#include "platform/opengl/OpenGLBuffer.h"

namespace Papaya
{

Ref<Buffer> Buffer::Create(const void* vertices, uint32_t size, BufferType type, BufferUsage usage)
{
  return CreateRef<OpenGLBuffer>(vertices, size, type, usage);
}

Buffer::~Buffer() {

}

} // namespace Papaya
