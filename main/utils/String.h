#ifndef String_h
#define String_h

#include <ostream>
#include <cstring>

namespace Papaya
{

  class String
  {
  public:
    ~String() { delete[] m_Buffer; }

    String();
    String(char *str);
    String(const char *str);

    String(const String &str);     // Copy Constructor
    String(String &&str) noexcept; // Move Constructor

    String &operator=(const String &str); // Copy Assignment Operator

    std::size_t Length() const { return m_Size; }
    const char *Raw() const { return m_Buffer; }

    friend std::ostream &operator<<(std::ostream &stream, const String &string);
    friend String operator+(const String &string, const String &other);

  private:
    char *m_Buffer;
    unsigned long long m_Size;
  };

} // namespace Papaya

#endif /* end of include guard: String_h */