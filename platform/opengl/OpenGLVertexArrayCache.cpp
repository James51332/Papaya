#include "OpenGLVertexArrayCache.h"

#include "main/utils/Hash.h"

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

namespace Papaya
{

std::unordered_map<int, Ref<OpenGLVertexArray>> OpenGLVertexArrayCache::s_Cache;

static int GenerateKey(const std::vector<Ref<Buffer>>& vertexBuffers,
                       const BufferLayout& layout,
                       const Ref<Buffer>& indexBuffer)
{
  // TODO: This is the core of the cache system. We need to minimize the risk
  // of the same value for multiple models and also have a fast algorithm.
  // I'm marking this as TODO because it is potentially a fault that should
  // be looked into if there are flaws in OpenGL rendering.

  // The system that we'll use is highly inspired by DiligentEngine/DiligentCore's
  // VAOCacheKey system. They use code from the boost library to combine keys from
  // an unset number of values. This feels sufficiently unlikely that the same 
  // key will be generated even though it's impossible. 

  std::size_t seed = 0;

  for (auto& vb : vertexBuffers)
    Papaya::HashCombine(seed, std::static_pointer_cast<OpenGLBuffer>(vb)->GetUniqueID()); // BufferID's start at 1000 and go up

  Papaya::HashCombine(seed, layout.GetStride());
  for (auto& element : layout)
  {
    Papaya::HashCombine(seed, element.Offset);
    Papaya::HashCombine(seed, element.Size);
  }

  Papaya::HashCombine(seed, indexBuffer ? std::static_pointer_cast<OpenGLBuffer>(indexBuffer)->GetUniqueID() : 0); // This should almost always be included

  return seed;
}

Ref<OpenGLVertexArray> OpenGLVertexArrayCache::GetVertexArray(const std::vector<Ref<Buffer>>& vertexBuffers, 
                                                              const BufferLayout& layout, 
                                                              const Ref<Buffer>& indexBuffer)
{
  int key = GenerateKey(vertexBuffers, layout, indexBuffer);

  auto vao = s_Cache.find(key);
  if (vao != s_Cache.end())
  {
    return vao->second;

  } else
  {
    // Create new VAO
  }
}

} // namespace Papaya
