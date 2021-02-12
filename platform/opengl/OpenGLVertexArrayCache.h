#ifndef OpenGLVertexArrayCache_h
#define OpenGLVertexArrayCache_h

#include "OpenGLVertexArray.h"

#include "main/renderer/Buffer.h"
#include "main/renderer/BufferLayout.h"

#include <unordered_map>
#include <vector>

namespace Papaya
{
  
class OpenGLVertexArrayCache
{
public:
  ~OpenGLVertexArrayCache();

  static Ref<OpenGLVertexArray> GetVertexArray(const std::vector<Ref<Buffer>>& vertexBuffers, 
                                               const BufferLayout& layout, 
                                               const Ref<Buffer>& indexBuffer);

private:
  static std::unordered_map<int, Ref<OpenGLVertexArray>> s_Cache;
};

} // namespace Papaya


#endif /* end of include guard: OpenGLVertexArrayCache_h */