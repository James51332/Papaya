#include "RenderCommand.h"

namespace Papaya
{
  Scope<RenderApi> RenderCommand::s_Api = RenderApi::Create();
  uint32_t RenderCommand::s_IndexSize = 4;
  uint32_t RenderCommand::s_IndexOffset = 0;
  uint32_t RenderCommand::s_ElementCount = 0;
} // namespace Papaya
