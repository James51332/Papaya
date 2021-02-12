#ifndef Renderer_h
#define Renderer_h

#include "main/utils/Memory.h"

#include "RenderApi.h"
#include "Buffer.h"
#include "BufferLayout.h"

#include <vector>

namespace Papaya
{
  
class Renderer
{
public:
  static void OnInit();
  static void OnTerminate();

  static void Begin();
  
  static void Submit(const std::vector<Ref<Buffer>> &vertexBuffers,
                     const BufferLayout &layout,
                     const Ref<Buffer> &indexBuffer,
                     const Ref<Shader> &shader);

  static void End();

  static RenderApi::API GetApi() { return s_Api; }

private:
  static RenderApi::API s_Api;
};

} // namespace Papaya


#endif /* end of include guard: Renderer_h */