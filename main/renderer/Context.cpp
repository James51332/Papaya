#include "Context.h"

#include "main/core/Log.h"

#include "platform/macos/CocoaContext.h"

namespace Papaya
{

Ref<Context> Context::Create(RenderApi api)
{
#ifdef PAPAYA_MACOS
  return CocoaContext::Create(api);
#endif

#ifdef PAPAYA_WINDOWS

#endif

  PAPAYA_ASSERT(false, "Rendering Contexts not supported on this platform yet!");
}

Context::~Context()
{

}

} // namespace Papaya
