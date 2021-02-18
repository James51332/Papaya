#include "OpenGLShader.h"
#include "OpenGLLoader.h"

#include <glm/gtc/type_ptr.hpp>

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

void OpenGLShader::SetFloat(const String& name, float value)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniform1f(location, value);
}

void OpenGLShader::SetFloat2(const String& name, const glm::vec2& value)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniform2f(location, value.x, value.y);
}

void OpenGLShader::SetFloat3(const String& name, const glm::vec3& value)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::SetFloat4(const String& name, const glm::vec4& value)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat2(const String& name, const glm::mat2& matrix)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetMat3(const String& name, const glm::mat3& matrix)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetMat4(const String& name, const glm::mat4& matrix)
{
  GLint location = glGetUniformLocation(m_RendererID, name.Raw());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace Papaya
