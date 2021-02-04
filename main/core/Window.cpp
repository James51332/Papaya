#include "Window.h"

#include "platform/macos/CocoaWindow.h"
#include "platform/windows/WindowsWindow.h"

#include "main/core/Log.h"

namespace Papaya
{

Scope<Window> Window::Create(const WindowAttribs& attribs) {
  Scope<Window> window;

#ifdef PAPAYA_MACOS
  window = CreateScope<CocoaWindow>(attribs);
  PAPAYA_CORE_INFO("Created Window: {}", m_Window);
  return Move(window);
#endif

#ifdef PAPAYA_WINDOWS
  window = CreateScope<WindowsWindow>(attribs);
  PAPAYA_CORE_INFO("Created Window: {}", m_Window);
  return Move(window);
#endif

  PAPAYA_ASSERT(false, "Window Creation is not supported on this platform!");
  return nullptr;
}

Window::~Window() {

}

} // namespace Papaya
