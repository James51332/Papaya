#pragma once

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

    virtual void SetData(const void *data, uint32_t size) = 0;

    virtual uint32_t GetSize() const = 0;
  };

} // namespace Papaya