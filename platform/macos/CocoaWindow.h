#ifndef CocoaWindow_h
#define CocoaWindow_h

#include "main/core/Window.h"

namespace Papaya
{

class CocoaWindow : public Window {
public:
  CocoaWindow(const WindowAttribs& attribs);
  ~CocoaWindow();

  void Show();
  void Hide();
  void Close();

  void SetContext(const Ref<Context>& context);

private:
  void* m_Window;
  void* m_Delegate;
};

} // namespace Papaya


#endif /* end of include guard: CocoaWindow_h */