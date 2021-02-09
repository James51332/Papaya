#ifndef Shader_h
#define Shader_h

#include "main/utils/Memory.h"
#include "main/utils/String.h"

namespace Papaya
{

class Shader {
public:
  static Ref<Shader> Create(const String& vertexSrc, const String& fragmentSrc);
  virtual ~Shader();

  virtual void Bind() = 0;
  virtual void Unbind() = 0;
};

} // namespace Papaya


#endif /* end of include guard: Shader_h */