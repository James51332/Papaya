#ifndef RenderApi_h
#define RenderApi_h

#include "Buffer.h"
#include "BufferLayout.h"
#include "Shader.h"

namespace Papaya
{

class RenderApi {
public:
  enum class API
  { // TODO: I don't know if we'll implement all of these but these are just the list of potential candidates
    None,
    OpenGL,
    DirectX,
    Metal,
    Vulkan,
  };

public:
  static Scope<RenderApi> Create();
  virtual ~RenderApi();

  virtual void ClearColor(float r, float g, float b, float a) = 0;
  virtual void Clear() = 0;

  virtual void DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                           const BufferLayout &layout,
                           const Ref<Buffer> &indexBuffer,
                           const Ref<Shader> &shader) = 0;
};

} // namespace Papaya


#endif /* end of include guard: RenderApi_h */