#pragma once

#include "main/renderer/Context.h"

#ifdef PAPAYA_WINDOWS
#include <windows.h>
#endif

namespace Papaya
{

  ////////////////////////////////////////////
  ///// WindowsContext ///////////////////////
  ////////////////////////////////////////////

  class WindowsContext : public Context
  {
  public:
    static Ref<Context> Create(const Scope<Window> &window, RenderApi::API api);
    virtual ~WindowsContext();

    virtual void SwapBuffers() = 0;
  };

  ////////////////////////////////////////////
  ///// WindowsOpenGLContext /////////////////
  ////////////////////////////////////////////

  class WindowsOpenGLContext : public WindowsContext
  {
  public:
    WindowsOpenGLContext(const Scope<Window> &window);
    virtual ~WindowsOpenGLContext();

    void MakeCurrent();
    void SwapBuffers();

  private:
#ifdef PAPAYA_WINDOWS
    HDC m_Hdc;
    HGLRC m_Hglrc;
#endif
  };

} // namespace Papaya