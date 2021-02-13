#ifndef RenderCommand_h
#define RenderCommand_h

#include "Buffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "RenderApi.h"

#include "main/utils/Memory.h"

namespace Papaya
{
    
class RenderCommand {
public:
static void OnInit() {}
static void OnTerminate() {}

static void ClearColor(float r, float g, float b, float a = 1.0f)
{
  s_Api->ClearColor(r, g, b, a);
}

static void Clear()
{
  s_Api->Clear();
}

static void DrawIndexed(const std::vector<Ref<Buffer>> &vertexBuffers,
                        const BufferLayout &layout,
                        const Ref<Buffer> &indexBuffer,
                        const Ref<Shader> &shader)

{
  s_Api->DrawIndexed(vertexBuffers, layout, indexBuffer, shader);
}

private:
  static Scope<RenderApi> s_Api;
};

} // namespace Papaya


#endif /* end of include guard: RenderCommand_h */