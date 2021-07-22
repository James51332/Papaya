#include "papayapch.h"
#include "String.h"

namespace Papaya
{

  String::String()
  {
    m_Size = 0;
    m_Buffer = new char[m_Size + 1];
    m_Buffer[m_Size] = 0;
  }

  String::String(char *str)
  {
    if (str != nullptr)
    {
      m_Size = strlen(str);
      m_Buffer = new char[m_Size + 1];
      strcpy(m_Buffer, str);
      m_Buffer[m_Size] = 0;
    }
    else
    {
      m_Size = 0;
      m_Buffer = new char[m_Size + 1];
      m_Buffer[m_Size] = 0;
    }
  }

  String::String(const char *str)
  {
    if (str != nullptr)
    {
      m_Size = strlen(str);
      m_Buffer = new char[m_Size + 1];
      strcpy(m_Buffer, str);
      m_Buffer[m_Size] = 0;
    }
    else
    {
      m_Size = 0;
      m_Buffer = new char[m_Size + 1];
      m_Buffer[0] = 0;
    }
  }

  String::String(const String &str)
  {
    m_Size = str.m_Size;
    m_Buffer = new char[m_Size + 1];
    strcpy(m_Buffer, str.m_Buffer);
  }

  String::String(String &&str) noexcept
  {
    m_Buffer = str.m_Buffer;
    m_Size = str.m_Size;

    str.m_Buffer = nullptr;
    str.m_Size = 0;
  }

  String &String::operator=(const String &str)
  {
    m_Size = str.m_Size;
    m_Buffer = new char[m_Size + 1];
    strcpy(m_Buffer, str.m_Buffer);

    return (*this);
  }

  void String::MakeSubstring(uint32_t begin, uint32_t end)
  {
    char* tmp = new char[m_Size + 1];
    strcpy(tmp, m_Buffer);

    m_Size = static_cast<uint64_t>(end) - static_cast<uint64_t>(begin) + 1; // String("0123567").Substring(1, 3) has a size of 3
    
    delete[] m_Buffer;
    m_Buffer = new char[m_Size + 1];
    
    tmp += begin;
    memcpy(m_Buffer, tmp, m_Size); // we have to use memcpy here because of different sizes. (I think)
    m_Buffer[m_Size] = 0;   
  }

  String String::Substring(uint32_t begin, uint32_t end)
  {
    int size = static_cast<uint64_t>(end) - static_cast<uint64_t>(begin) + 1;
    char* buf = new char[size + 1];
    memcpy(buf, m_Buffer + begin, size);
    buf[size] = 0;
    return buf;
  }

  std::ostream &operator<<(std::ostream &stream, const String &string)
  {
    return stream << string.m_Buffer;
  }

  String operator+(const String& string, const String& other)
  {
    char* buffer = new char[string.m_Size + other.m_Size + 1];

    strcpy(buffer, string.m_Buffer);
    strcat(buffer, other.m_Buffer);

    return buffer;
  }

  bool operator==(const String& string, const String& other)
  {
    return !strcmp(string.m_Buffer, other.m_Buffer);
  }

  bool operator!=(const String& string, const String& other)
  {
    return !(string == other);
  }

} // namespace Papaya