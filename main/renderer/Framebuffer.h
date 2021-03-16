#pragma once

#include "main/renderer/Texture.h"

#include "main/utils/Memory.h"

namespace Papaya
{
  
struct FramebufferDesc
{
uint32_t Width, Height;

int Samples = 1;

bool InSwapChain = false;
};

class Framebuffer
{
public:
  static Ref<Framebuffer> Create(const FramebufferDesc& desc);
  virtual ~Framebuffer();

  virtual Ref<Texture2D>& GetColorTexture() = 0;

  virtual void Resize(uint32_t width, uint32_t height) = 0;
  virtual void Invalidate() = 0;

  virtual void Bind() = 0;
  virtual void Unbind() = 0;

protected:
  FramebufferDesc m_Desc;
};

} // namespace Papaya
