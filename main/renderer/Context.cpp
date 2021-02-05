#include "Context.h"

#include "main/core/Window.h"
#include "main/core/Log.h"

#include "platform/macos/CocoaContext.h"
#include "platform/windows/WindowsContext.h"

#define PAPAYA_GL_LITE_IMPLEMENTATION
#include "platform/opengl/OpenGLLoader.h"

namespace Papaya
{

bool Context::s_OpenGLInitialized = false;

Ref<Context> Context::Create(const Scope<Window>& window, RenderApi api)
{

#ifdef PAPAYA_MACOS
  if (!s_OpenGLInitialized)
  {
    InitOpenGL();
    s_OpenGLInitialized = true;
  }
#endif

#ifdef PAPAYA_MACOS
  return CocoaContext::Create(window, api);
#endif

#ifdef PAPAYA_WINDOWS
  return WindowsContext::Create(window, api);
#endif

  PAPAYA_ASSERT(false, "Rendering Contexts not supported on this platform yet!");
  return nullptr;
}

Context::~Context()
{

}

} // namespace Papaya
