#include "PipelineState.h"

#include "platform/opengl/OpenGLPipelineState.h"

namespace Papaya
{

  Ref<PipelineState> PipelineState::Create(const PipelineStateDesc &desc)
  {
    return CreateRef<OpenGLPipelineState>(desc);
  }

  PipelineState::~PipelineState()
  {
  }

} // namespace Papaya
