#include "papayapch.h"
#include "Framebuffer.h"



#include "main/renderer/Renderer.h"
#include "main/renderer/RenderApi.h"

#include "platform/opengl/OpenGLFramebuffer.h"

namespace Papaya {

Ref<Framebuffer> Framebuffer::Create(const FramebufferDesc& desc)
{
  switch (Renderer::GetApi())
  {
  case RenderApi::API::OpenGL: { return CreateRef<OpenGLFramebuffer>(desc); }
  default: break;
  }

  PAPAYA_ASSERT(false, "Unknown Rendering API!");
  return nullptr;
}

Framebuffer::~Framebuffer() {
  
}

} // namespace Papaya