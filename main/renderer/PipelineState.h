#ifndef PipelineState_h
#define PipelineState_h

#include "Shader.h"
#include "BufferLayout.h"

#include "main/utils/Memory.h"

namespace Papaya
{

  // This struct will become more compilicated over time but we don't
  // need a lot of the advanced shader features right now.
  struct PipelineStateDesc
  {
    Ref<Shader> Shader;
    VertexDescriptor Layout;

    PipelineStateDesc() = default;
  };

  class PipelineState
  {
  public:
    static Ref<PipelineState> Create(const PipelineStateDesc &desc);
    virtual ~PipelineState();

    // This API may change with time. A possible idea is to build out the RenderDevice
    // type and store a reference to a bound pipeline state. This way uploading uniforms
    // is a static call (maybe something like RenderDevice::SetUniform()) and simply uses
    // the bound object to upload.
    virtual Ref<Shader> &GetShader() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
  };

} // namespace Papaya

#endif /* end of include guard: PipelineState_h */