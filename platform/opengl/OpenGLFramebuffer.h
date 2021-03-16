#pragma once

#include "main/renderer/Framebuffer.h"

namespace Papaya
{
  class OpenGLFramebuffer : public Framebuffer
  {
  public:
    OpenGLFramebuffer(const FramebufferDesc& desc);
    virtual ~OpenGLFramebuffer();

    Ref<Texture2D>& GetColorTexture() { return m_ColorTexture; }

    void Resize(uint32_t width, uint32_t height);
    void Invalidate();

    void Bind();
    void Unbind();

  private:
    uint32_t m_RendererID = 0;
    Ref<Texture2D> m_ColorTexture;
  };

} // namespace Papaya
