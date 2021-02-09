#ifndef VertexArray_h
#define VertexArray_h

#include "Buffer.h"

#include "main/utils/Memory.h"

namespace Papaya
{

class VertexArray
{
public:
  static Ref<VertexArray> Create();
  virtual ~VertexArray();

  virtual void SetVertexBuffer(const Ref<Buffer>& buffer) = 0;
  virtual void SetIndexBuffer(const Ref<Buffer>& buffer) = 0;

  //These methods will cause segfault if vertex and index buffers aren't set
  virtual void Bind() = 0;
  virtual void Unbind() = 0;
};

} // namespace Papaya


#endif /* end of include guard: VertexArray_h */