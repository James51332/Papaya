#include "String.h"

namespace Papaya {

  String::String() {
    m_Size = 0;
    m_Buffer = new char[m_Size + 1];
    m_Buffer[0] = 0;
  }

  String::String(char* str) {
    if (str != nullptr)
    {
      m_Size = strlen(str);
      m_Buffer = new char[m_Size + 1];
      strcpy(m_Buffer, str);
      m_Buffer[m_Size] = 0;
    } else {
      m_Size = 0;
      m_Buffer = new char[m_Size + 1];
      m_Buffer[0] = 0;
    }
  }

  String::String(const char* str) {
    if (str != nullptr)
    {
      m_Size = strlen(str);
      m_Buffer = new char[m_Size + 1];
      strcpy(m_Buffer, str);
      m_Buffer[m_Size] = 0;
    } else {
      m_Size = 0;
      m_Buffer = new char[m_Size + 1];
      m_Buffer[0] = 0;
    }
  }

  String::String(const String& str) {
    m_Size = str.m_Size;
    m_Buffer = new char[m_Size];
    strcpy(m_Buffer, str.m_Buffer);
  }

  String::String(String&& str) noexcept {
    m_Buffer = str.m_Buffer;
    m_Size = str.m_Size;

    str.m_Buffer = nullptr;
    str.m_Size = 0;
  } 

  String& String::operator=(const String& str) {
    m_Size = str.m_Size;
    m_Buffer = new char[m_Size];
    strcpy(m_Buffer, str.m_Buffer);

    return (*this);
  }

  std::ostream& operator<<(std::ostream& stream, const String& string) {
    return stream << string.m_Buffer;
  }

  String operator+(const String& string, const String& other) {
    char* buffer = new char[string.m_Size + other.m_Size + 1];
    
    strcpy(buffer, string.m_Buffer);
    strcat(buffer, other.m_Buffer);
    
    return buffer;
  }

} // namespace Papaya