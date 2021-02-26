#ifndef OpenGLShader_h
#define OpenGLShader_h

#include "main/renderer/Shader.h"

namespace Papaya
{

  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader(const String &vertexSrc, const String &fragmentSrc);
    virtual ~OpenGLShader();

    void Bind();
    void Unbind();

    void SetInt(const String &name, int32_t value);
    void SetIntArray(const String &name, int *values, uint32_t count);

    void SetFloat(const String &name, float value);
    void SetFloat2(const String &name, const glm::vec2 &value);
    void SetFloat3(const String &name, const glm::vec3 &value);
    void SetFloat4(const String &name, const glm::vec4 &value);

    void SetMat2(const String &name, const glm::mat2 &matrix);
    void SetMat3(const String &name, const glm::mat3 &matrix);
    void SetMat4(const String &name, const glm::mat4 &matrix);

  private:
    unsigned int m_RendererID;
  };

} // namespace Papaya

#endif /* end of include guard: OpenGLShader_h */