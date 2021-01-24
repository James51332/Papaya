#include "Platform.h"

#include "platform/macos/CocoaPlatform.h"

#include "main/core/Log.h"

namespace Papaya
{

Scope<Platform> Platform::s_Instance = Platform::Create();

void Platform::OnInit() {
  s_Instance->Init();
}

void Platform::OnUpdate() {
  s_Instance->Update();
}

void Platform::OnTerminate() {
  s_Instance->Terminate();
}

Scope<Platform> Platform::Create() {
#ifdef PAPAYA_MACOS
  return CreateScope<CocoaPlatform>();
#endif

#ifdef PAPAYA_WINDOWS

#endif

  PAPAYA_ASSERT(false, "Unsupported Platform!");
  return nullptr;
}

Platform::Platform() {

}

Platform::~Platform() {

}

} // namespace Papaya
