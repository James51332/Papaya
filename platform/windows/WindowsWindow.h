#ifndef WindowsWindow_h
#define WindowsWindow_h

#include "main/core/Window.h"

#include "platform/windows/WindowsContext.h"

#ifdef PAPAYA_WINDOWS
#include <Windows.h>
#endif

namespace Papaya
{

  class WindowsWindow : public Window
  {
    friend WindowsOpenGLContext;

  public:
    WindowsWindow(const WindowAttribs &attribs);
    virtual ~WindowsWindow();

    void Show();
    void Hide();
    void Close();

    void OnUpdate();

    void SetContext(const Ref<Context> &context);

  private:
#ifdef PAPAYA_WINDOWS
    HWND m_Hwnd;
#endif
    static bool s_KeyCodesInitialized;
  };

} // namespace Papaya

#endif /* end of include guard: WindowsWindow_h */