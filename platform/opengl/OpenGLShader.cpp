#include "OpenGLShader.h"
#include "OpenGLLoader.h"

namespace Papaya
{

OpenGLShader::OpenGLShader(const String& vertexSrc, const String& fragmentSrc)
{
  const char* vertex = vertexSrc.Raw();
  const char* fragment = fragmentSrc.Raw();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment, NULL);
  glCompileShader(fragmentShader);

  m_RendererID = glCreateProgram();
  glAttachShader(m_RendererID, vertexShader);
  glAttachShader(m_RendererID, fragmentShader);
  glLinkProgram(m_RendererID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader()
{

}

void OpenGLShader::Bind()
{
  glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind()
{
  glUseProgram(0);
}

} // namespace Papaya
