#ifndef Shader_h
#define Shader_h

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include <glm/matrix.hpp>

namespace Papaya
{

  class Shader
  {
  public:
    static Ref<Shader> Create(const String &vertexSrc, const String &fragmentSrc);
    virtual ~Shader();

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    // TODO: Next-Gen API's support uploading buffers as uniforms
    // those may give better performance than uploading per frame
    virtual void SetInt(const String &name, int32_t value) = 0;
    virtual void SetIntArray(const String &name, int *values, uint32_t count) = 0;

    virtual void SetFloat(const String &name, float value) = 0;
    virtual void SetFloat2(const String &name, const glm::vec2 &value) = 0;
    virtual void SetFloat3(const String &name, const glm::vec3 &value) = 0;
    virtual void SetFloat4(const String &name, const glm::vec4 &value) = 0;

    virtual void SetMat2(const String &name, const glm::mat2 &matrix) = 0;
    virtual void SetMat3(const String &name, const glm::mat3 &matrix) = 0;
    virtual void SetMat4(const String &name, const glm::mat4 &matrix) = 0;
  };

} // namespace Papaya

#endif /* end of include guard: Shader_h */