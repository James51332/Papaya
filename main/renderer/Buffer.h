#pragma once

namespace Papaya
{

  enum class BufferUsage
  {
    Immutable,
    Dynamic,
    Stream
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
    static Ref<Buffer> Create();
    virtual ~Buffer();

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetData(const void *data, uint32_t size) = 0; // Efficient
    virtual void Reset(const void *data, uint32_t size, BufferType type, BufferUsage usage) = 0; // Inefficient 

    virtual uint32_t GetSize() const = 0;
  };

} // namespace Papaya