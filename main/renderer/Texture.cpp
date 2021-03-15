#include "Texture.h"

#include "main/core/Log.h"

#include "Renderer.h"

#include "platform/opengl/OpenGLTexture.h"

namespace Papaya
{

  Ref<Texture2D> Texture2D::Create(const String& path)
  {
    switch (Renderer::GetApi())
    {
    case RenderApi::API::OpenGL: { return CreateRef<OpenGLTexture2D>(path); }
    default: break;
    }

    PAPAYA_ASSERT(false, "Unknown Rendering API!");
    return nullptr;
  }

  Ref<Texture2D> Texture2D::Create(const unsigned char* data, uint32_t width, uint32_t height, ChannelType channels)
  {
    switch (Renderer::GetApi())
    {
    case RenderApi::API::OpenGL: { return CreateRef<OpenGLTexture2D>(data, width, height, channels); }
    default: break;
    }

    PAPAYA_ASSERT(false, "Unknown Rendering API!");
    return nullptr;
  }

  Ref<Texture2D> Texture2D::Create(const uint32_t* data, uint32_t width, uint32_t height, ChannelType channels)
  {
    switch (Renderer::GetApi())
    {
    case RenderApi::API::OpenGL: { return CreateRef<OpenGLTexture2D>(data, width, height, channels); }
    default: break;
    }

    PAPAYA_ASSERT(false, "Unknown Rendering API!");
    return nullptr;
  }

} // namespace Papaya
