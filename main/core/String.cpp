#include "String.h"

namespace Papaya
{

String::String()
  : m_Chars{ nullptr }
{
  m_Chars = new char[1];
  m_Chars[0] = '\0';
}

String::String(char* str)
  : m_Chars{ nullptr }
{
  if (str == nullptr) {
    m_Chars = new char[1];
    m_Chars[0] = '\0';
  }
  else
  {
    m_Chars = new char[strlen(str) + 1];
    strcpy(m_Chars, str);
  }
}

String::String(const char* str)
  : m_Chars{ nullptr }
{
  if (str == nullptr) {
    m_Chars = new char[1];
    m_Chars[0] = '\0';
  }
  else
  {
    m_Chars = new char[strlen(str) + 1];
    strcpy(m_Chars, str);
  }
}

String::String(const String& source)
  : m_Chars{ nullptr }
{
  m_Chars = new char[strlen(source.m_Chars) + 1];
  strcpy(m_Chars, source.m_Chars);
}

String::String(String&& source)
{
  m_Chars = source.m_Chars;
  source.m_Chars = nullptr;
}

int String::Length() const {
  return strlen(m_Chars);
}

void String::Append(const String& str)
{
  if (str.m_Chars == nullptr)
    return;

  m_Chars = new char[strlen(m_Chars) + strlen(str.m_Chars) + 1];
  strcpy(m_Chars + sizeof(m_Chars), str.m_Chars);
  m_Chars[strlen(m_Chars) - 1] = '\0';
}

const char* String::Raw() const {
  return m_Chars;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
  return os << s.m_Chars;
}


String operator+(const String& lhs, const String& rhs)
{
  char* c = new char[strlen(lhs.m_Chars) + strlen(rhs.m_Chars) + 1];
  strcpy(lhs.m_Chars + strlen(lhs.m_Chars) * sizeof(char), rhs.m_Chars);
  return String(c);
}



} // namespace Papaya
