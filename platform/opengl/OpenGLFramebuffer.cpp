#include "papayapch.h"
#include "OpenGLFramebuffer.h"
#include "OpenGLLoader.h"

#include "OpenGLTexture.h"



namespace Papaya {

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferDesc& desc)
{
  m_Desc = desc;

  Invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer() 
{
  glDeleteFramebuffers(1, &m_RendererID);
}

void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
{
  m_Desc.Width = width;
  m_Desc.Height = height;

  Invalidate();
}

void OpenGLFramebuffer::Invalidate() 
{
  if (m_RendererID)
  {
    glDeleteFramebuffers(1, &m_RendererID);
  }

  glGenFramebuffers(1, &m_RendererID);
  glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

  m_ColorTexture = Texture2D::Create((uint32_t*)nullptr, m_Desc.Width, m_Desc.Height, ChannelType::RGB);
  m_ColorTexture->Bind();
  
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, std::static_pointer_cast<OpenGLTexture2D>(m_ColorTexture)->m_RendererID, 0);

  PAPAYA_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER), "Failed to Create Framebuffer");
}

void OpenGLFramebuffer::Bind() 
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
  glViewport(0, 0, m_Desc.Width, m_Desc.Height);
}

void OpenGLFramebuffer::Unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace Papaya