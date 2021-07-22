#pragma once

#include "main/renderer/RenderApi.h"

namespace Papaya
{

  class Context;

  struct WindowAttribs
  {
    int Width, Height;
    String Title;
    bool Resizable;
    RenderApi::API Api;

    WindowAttribs(int width = 800, int height = 600, const String& title = "Papaya", bool resizable = false, RenderApi::API api = RenderApi::API::OpenGL)
        : Width(width), Height(height), Title(title), Resizable(resizable), Api(api) {}

    String ToString() const
    {
      std::stringstream ss;
      ss << "(Width: " << Width << ", Height: " << Height << ", Title: " << Title << ", Resizable: " << (Resizable ? "Yes" : "No") << ")";
      return ss.str().c_str();
    }
  };

  inline std::ostream &operator<<(std::ostream &stream, const WindowAttribs &attribs)
  {
    return stream << attribs.ToString();
  }

  class Window
  {
    friend class Context;

  public:
    static Scope<Window> Create(const WindowAttribs &attribs = WindowAttribs());
    virtual ~Window();

    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Close() = 0;

    virtual void OnUpdate() = 0;

    virtual void SetContext(const Ref<Context> &context) = 0;

    Ref<Context> GetContext() const { return m_Context; }
    const WindowAttribs &GetAttribs() const { return m_Attribs; }

  protected:
    WindowAttribs m_Attribs;
    Ref<Context> m_Context;
  };

  inline std::ostream &operator<<(std::ostream &os, const Scope<Window> &window)
  {
    return os << window->GetAttribs();
  }

} // namespace Papaya