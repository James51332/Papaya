#include "Context.h"

#include "main/core/Log.h"

#include "platform/macos/CocoaContext.h"

#define PAPAYA_GL_LITE_IMPLEMENTATION
#include "platform/opengl/OpenGLLoader.h"

namespace Papaya
{

bool Context::s_OpenGLInitialized = false;

Ref<Context> Context::Create(RenderApi api)
{
  if (!s_OpenGLInitialized)
  {
    InitOpenGL();
    s_OpenGLInitialized = true;
  }

#ifdef PAPAYA_MACOS
  return CocoaContext::Create(api);
#endif

#ifdef PAPAYA_WINDOWS

#endif

  PAPAYA_ASSERT(false, "Rendering Contexts not supported on this platform yet!");
  return nullptr;
}

Context::~Context()
{

}

} // namespace Papaya
