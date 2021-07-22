#include "papayapch.h"
#include "OpenGLPipelineState.h"

namespace Papaya
{

  OpenGLPipelineState::OpenGLPipelineState(const PipelineStateDesc &desc)
  {
    m_Shader = desc.Shader;
    m_Layout = desc.Layout;
  }

  OpenGLPipelineState::~OpenGLPipelineState()
  {
  }

  void OpenGLPipelineState::Bind()
  {
    m_Shader->Bind();
  }

  void OpenGLPipelineState::Unbind()
  {
  }

} // namespace Papaya
