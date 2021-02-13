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
    BufferLayout Layout;

    PipelineStateDesc() = default;
  };

  class PipelineState
  {
  public:
    static Ref<PipelineState> Create(const PipelineStateDesc &desc);
    virtual ~PipelineState();

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
  };

} // namespace Papaya

#endif /* end of include guard: PipelineState_h */