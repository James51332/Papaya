#ifndef OpenGLShader_h
#define OpenGLShader_h

#include "main/renderer/Shader.h"

namespace Papaya
{

class OpenGLShader : public Shader
{
public:
  OpenGLShader(const String& vertexSrc, const String& fragmentSrc);
  virtual ~OpenGLShader();

  void Bind();
  void Unbind();

private:
  unsigned int m_RendererID;
};

} // namespace Papaya

#endif /* end of include guard: OpenGLShader_h */