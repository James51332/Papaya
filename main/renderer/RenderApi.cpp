#include "RenderApi.h"

#include "platform/opengl/OpenGLRenderApi.h"

namespace Papaya
{

Scope<RenderApi> RenderApi::Create()
{
  // TODO: Implement switching on api's
  return CreateScope<OpenGLRenderApi>();
}

RenderApi::~RenderApi()
{

}

} // namespace Papaya
