#include "papayapch.h"
#include "Window.h"

#include "main/renderer/Context.h"

#include "platform/macos/CocoaWindow.h"
#include "platform/windows/WindowsWindow.h"

#include "platform/macos/CocoaContext.h"

#include "papayapch.h"


namespace Papaya
{

  Scope<Window> Window::Create(const WindowAttribs &attribs)
  {
    Scope<Window> window;
    Ref<Context> context;

#ifdef PAPAYA_MACOS
    window = CreateScope<CocoaWindow>(attribs);
    context = Context::Create(window, attribs.Api);

    window->SetContext(context);

    PAPAYA_CORE_TRACE("Created Window: {}", window);
    return Move(window);
#endif

#ifdef PAPAYA_WINDOWS
    window = CreateScope<WindowsWindow>(attribs);
    context = Context::Create(window, attribs.Api);

    window->SetContext(context);

    PAPAYA_CORE_TRACE("Created Window: {}", window);
    return Move(window);
#endif

    PAPAYA_ASSERT(false, "Window Creation is not supported on this platform!");
    return nullptr;
  }

  Window::~Window()
  {
  }

} // namespace Papaya
