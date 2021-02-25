#ifndef Buffer_h
#define Buffer_h

#include "main/utils/String.h"
#include "main/utils/Memory.h"

namespace Papaya
{

  enum class BufferUsage
  {
    Immutable,
    Dynamic
  };

  enum class BufferType
  {
    Vertex,
    Index
  };

  class Buffer
  {
  public:
    static Ref<Buffer> Create(const void *data, uint32_t size, BufferType type, BufferUsage usage);
    virtual ~Buffer();

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual uint32_t GetSize() const = 0;
  };

} // namespace Papaya

#endif /* end of include guard: Buffer_h */