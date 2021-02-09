#include "Shader.h"

#include "platform/opengl/OpenGLShader.h"

namespace Papaya
{

Ref<Shader> Shader::Create(const String& vertexSrc, const String& fragmentSrc)
{
  return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
}

Shader::~Shader()
{

}

} // namespace Papaya
