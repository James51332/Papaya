#ifndef String_h
#define String_h

#include <ostream>
#include <cstring>

namespace Papaya
{

class String {
public:
  String();
  String(char* val);
  String(const char* val);
  String(const String& source);
  String(String&& source);
  ~String() { delete m_Chars; }

  int Length();
  void Append(const String& s);

  friend std::ostream& operator<<(std::ostream& os, const String& s);
  friend String operator+(const String& lhs, const String& rhs);

private:
  char* m_Chars;
};

} // namespace Papaya


#endif /* end of include guard: String_h */