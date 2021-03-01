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

  Ref<Context> Context::Create(const Scope<Window> &window, RenderApi::API api)
  {

    Ref<Context> context;

#ifdef PAPAYA_MACOS
    context = CocoaContext::Create(window, api);

    if (!s_OpenGLInitialized && api == RenderApi::API::OpenGL)
    {
      InitOpenGL();
      s_OpenGLInitialized = true;
    }

    return context;
#endif

#ifdef PAPAYA_WINDOWS
    context = WindowsContext::Create(window, api);

    // Moved to MakeCurrent()
    if (!s_OpenGLInitialized && api == RenderApi::API::OpenGL)
    {
      InitOpenGL();
      s_OpenGLInitialized = true;
    }

    return context;
#endif

    PAPAYA_ASSERT(false, "Rendering Contexts not supported on this platform yet!");
    return nullptr;
  }

  Context::~Context()
  {
  }

} // namespace Papaya
