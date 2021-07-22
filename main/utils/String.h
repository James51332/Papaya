#pragma once

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

    void MakeSubstring(uint32_t begin, uint32_t end);
    String Substring(uint32_t begin, uint32_t end);

    friend std::ostream &operator<<(std::ostream &stream, const String &string);
    friend String operator+(const String &string, const String &other);
    friend bool operator==(const String& string, const String& other);
    friend bool operator!=(const String& string, const String& other);

    char& operator[](int index) { PAPAYA_ASSERT((index >= 0) && (index < m_Size), "String index out of bounds!"); return m_Buffer[index]; }
    char operator[](int index) const { PAPAYA_ASSERT((index >= 0) && (index < m_Size), "String index out of bounds!"); return m_Buffer[index]; }

    // TODO: Create begin() and end() methods

  private:
    char *m_Buffer;
    unsigned long long m_Size;
  };

} // namespace Papaya