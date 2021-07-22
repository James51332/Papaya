#pragma once

namespace Papaya
{

  enum class ChannelType
  {
    RGB,
    RGBA
  };

  class Texture
  {
  public:
    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void Bind(uint32_t slot = 0) const = 0;

    virtual bool operator==(const Texture& other) const = 0;
  };

  class Texture2D : public Texture
  {
  public:
    virtual ~Texture2D() = default;

    static Ref<Texture2D> Create(const String &path);
    static Ref<Texture2D> Create(const unsigned char* data, uint32_t width, uint32_t height, ChannelType channels);
    static Ref<Texture2D> Create(const uint32_t* data, uint32_t width, uint32_t height, ChannelType channels);
  };

} // namespace Papaya
