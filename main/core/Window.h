#ifndef Window_h
#define Window_h

#include "main/core/Memory.h"
#include "main/core/String.h"
#include "main/core/Log.h"

#include <sstream>

namespace Papaya
{

struct WindowAttribs {
  int Width, Height;
  String Title;
  bool Resizable;

  WindowAttribs(int width = 800, int height = 600, String title = "Papaya", bool resizable = false)
    : Width(width), Height(height), Title(title), Resizable(resizable) {}
};

class Window {
public:
  static Scope<Window> Create(const WindowAttribs& attribs = WindowAttribs()); // It's okay to copy because this won't happen frequently
  virtual ~Window();

  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void Close() = 0;

  const WindowAttribs& GetAttribs() { return m_Attribs; }

protected:
  WindowAttribs m_Attribs;
};

} // namespace Papaya


#endif /* end of include guard: Window_h */