#include "Platform.h"

#include "platform/macos/CocoaPlatform.h"
#include "platform/windows/WindowsPlatform.h"

#include "main/core/Log.h"

#include <iostream>
#include <sstream>
#include <fstream>

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

double Platform::GetSysTime() {
  return s_Instance->SysTime();
}

String Platform::LoadFile(const String& path)
{
	std::ifstream stream(path.Raw());

	if (!stream.is_open())
	{
		PAPAYA_CORE_ERROR("Failed to load file: {}", path);
	}

	std::stringstream ss;
	ss << stream.rdbuf();

	return ss.str().c_str();
}

void Platform::WriteFile(const String& path, const String& data)
{
  std::ofstream stream;
  stream.open(path.Raw());
  stream << data.Raw();
  stream.close();
}

Scope<Platform> Platform::Create() {
#ifdef PAPAYA_MACOS
  return CreateScope<CocoaPlatform>();
#endif

#ifdef PAPAYA_WINDOWS
  return CreateScope<WindowsPlatform>();
#endif

  PAPAYA_ASSERT(false, "Unsupported Platform!");
  return nullptr;
}

Platform::Platform() {

}

Platform::~Platform() {

}

} // namespace Papaya
