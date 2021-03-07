#pragma once
#include "main/core/Window.h"

namespace Papaya
{

  class CocoaWindow : public Window
  {
  public:
    CocoaWindow(const WindowAttribs &attribs);
    ~CocoaWindow();

    void Show();
    void Hide();
    void Close();

    void SetContext(const Ref<Context> &context);
    void OnUpdate();

  private:
    void *m_Window;
    void *m_Delegate;
  };

} // namespace Papaya