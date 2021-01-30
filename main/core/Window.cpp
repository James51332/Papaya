#include "Window.h"

#include "platform/macos/CocoaWindow.h"
#include "platform/windows/WindowsWindow.h"

#include "main/core/Log.h"

namespace Papaya
{

Scope<Window> Window::Create(const WindowAttribs& attribs) {
#ifdef PAPAYA_MACOS
  return CreateScope<CocoaWindow>(attribs);
#endif

#ifdef PAPAYA_WINDOWS
  return CreateScope<WindowsWindow>(attribs);
#endif

  PAPAYA_ASSERT(false, "Unsupported Platform!");
  return nullptr;
}

Window::~Window() {

}

} // namespace Papaya
