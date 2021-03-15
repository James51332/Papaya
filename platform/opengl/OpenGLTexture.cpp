#include "OpenGLTexture.h"
#include "OpenGLLoader.h"

#include "main/core/Log.h"

#include <stb_image.h>

namespace Papaya
{

  static GLenum ChannelTypeToGLenum(ChannelType type)
  {
    switch (type)
    {
    case ChannelType::RGB:
    {
      return GL_RGB;
      break;
    }

    case ChannelType::RGBA:
    {
      return GL_RGBA;
      break;
    }

    default:
      break;
    }

    PAPAYA_ASSERT(false, "Unknown ChannelType!");
    return 0;
  }

  OpenGLTexture2D::OpenGLTexture2D(const String& path)
    : m_Path(path)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path.Raw(), &width, &height, &channels, 0);
    PAPAYA_ASSERT(data, "Failed to load image");
    m_Width = width;
    m_Height = height;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    GLenum internal = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internal, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
  }

  OpenGLTexture2D::OpenGLTexture2D(const unsigned char* data, uint32_t width, uint32_t height, ChannelType channels)
  {
    m_Width = width;
    m_Height = height;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
      0,
      ChannelTypeToGLenum(channels),
      m_Width,
      m_Height,
      0,
      ChannelTypeToGLenum(channels),
      GL_UNSIGNED_BYTE,
      data);

    glGenerateMipmap(GL_TEXTURE_2D);
  }

  OpenGLTexture2D::OpenGLTexture2D(const uint32_t* data, uint32_t width, uint32_t height, ChannelType channels)
  {
    m_Width = width;
    m_Height = height;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
      0,
      ChannelTypeToGLenum(channels),
      m_Width,
      m_Height,
      0,
      ChannelTypeToGLenum(channels),
      GL_UNSIGNED_BYTE,
      data);

    glGenerateMipmap(GL_TEXTURE_2D);
  }

  OpenGLTexture2D::~OpenGLTexture2D()
  {
    glDeleteTextures(1, &m_RendererID);
  }

  void OpenGLTexture2D::Bind(uint32_t slot) const
  {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
  }

} // namespace Papaya
