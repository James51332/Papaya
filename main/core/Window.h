#ifndef Window_h
#define Window_h

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include "main/core/Log.h"

#include <sstream>

namespace Papaya
{

struct WindowAttribs {
  int Width, Height;
  String Title;
  bool Resizable;

  WindowAttribs(int width = 800, int height = 600, const String& title = "Papaya", bool resizable = false)
    : Width(width), Height(height), Title(title), Resizable(resizable) {}

  String ToString() const {
    std::stringstream ss;
    ss << "(Width: " << Width << ", Height: " << Height << ", Title: " << Title << ", Resizable: " << (Resizable ? "Yes" : "No") << ")";
    return ss.str().c_str();
  }
};

inline std::ostream& operator<<(std::ostream& stream, const WindowAttribs& attribs) {
  return stream << attribs.ToString();
}

class Window {
public:
  static Scope<Window> Create(const WindowAttribs& attribs = WindowAttribs());
  virtual ~Window();

  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void Close() = 0;

  const WindowAttribs& GetAttribs() { PAPAYA_CORE_TRACE(m_Attribs.Title + " GetAttribs()"); return m_Attribs; };

protected:
  WindowAttribs m_Attribs;
};

} // namespace Papaya


#endif /* end of include guard: Window_h */