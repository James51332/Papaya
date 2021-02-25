#pragma once

#include "main/utils/Memory.h"
#include "main/utils/String.h"

namespace Papaya
{

  class Texture
  {
  public:
    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void Bind(uint32_t slot = 0) const = 0;
  };

  class Texture2D : public Texture
  {
  public:
    virtual ~Texture2D() = default;

    static Ref<Texture2D> Create(const String &path);
  };

} // namespace Papaya
