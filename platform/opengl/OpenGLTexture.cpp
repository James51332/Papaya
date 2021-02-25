#include "OpenGLTexture.h"
#include "OpenGLLoader.h"

#include "main/core/Log.h"

#include <stb_image.h>

namespace Papaya
{

  OpenGLTexture2D::OpenGLTexture2D(const String &path)
      : m_Path(path)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(path.Raw(), &width, &height, &channels, 0);
    PAPAYA_ASSERT(data, "Failed to load image");
    m_Width = width;
    m_Height = height;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
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
