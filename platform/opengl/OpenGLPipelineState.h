#pragma once

#include "main/renderer/PipelineState.h"

#include "OpenGLVertexArrayCache.h"

namespace Papaya
{
  class Renderer;

  // The implementation for OpenGL is very simple.
  // It's just a wrapper around a shader and buffer layout.
  // In the future, this will help to cleanly implement
  // other API's where a PipelineState is an actual
  // primitive.
  class OpenGLPipelineState : public PipelineState
  {
    friend class OpenGLVertexArrayCache;
      
  public:
    OpenGLPipelineState(const PipelineStateDesc &desc);
    virtual ~OpenGLPipelineState();

    Ref<Shader> &GetShader() { return m_Shader; }
    const VertexDescriptor& GetLayout() const { return m_Layout; }

    void Bind();
    void Unbind();

  private:
    Ref<Shader> m_Shader;
    VertexDescriptor m_Layout;
  };

} // namespace Papaya
