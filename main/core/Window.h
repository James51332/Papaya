#ifndef Window_h
#define Window_h

#include "main/utils/Memory.h"
#include "main/utils/String.h"

#include "main/core/Log.h"

#include "main/renderer/Context.h"

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

  virtual void SetContext(const Ref<Context>& context) = 0;
  const WindowAttribs& GetAttribs() const { return m_Attribs; }

protected:
  WindowAttribs m_Attribs;
};

inline std::ostream& operator<<(std::ostream& os, const Scope<Window>& window)
{
  return os << window->GetAttribs();
}

} // namespace Papaya


#endif /* end of include guard: Window_h */