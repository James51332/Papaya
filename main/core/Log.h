#pragma once

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

#include "main/utils/Memory.h"

#include <cstring>
#include <ostream>
#include <sstream>

namespace Papaya
{

  class Log
  {
  public:
    static void OnInit();

    inline static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
    inline static Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    inline static std::ostringstream& GetCoreStream() { return s_CoreStream; }
    inline static std::ostringstream& GetClientStream() { return s_ClientStream; }

  private:
    static Ref<spdlog::logger> s_CoreLogger;
    static Ref<spdlog::logger> s_ClientLogger;

    static std::ostringstream s_CoreStream;
    static std::ostringstream s_ClientStream;
  };

#ifdef PAPAYA_DEBUG

#define PAPAYA_CORE_INFO(...) ::Papaya::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PAPAYA_CORE_TRACE(...) ::Papaya::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PAPAYA_CORE_WARN(...) ::Papaya::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PAPAYA_CORE_ERROR(...) ::Papaya::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PAPAYA_CORE_FATAL(...) ::Papaya::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define PAPAYA_INFO(...) ::Papaya::Log::GetClientLogger()->info(__VA_ARGS__)
#define PAPAYA_TRACE(...) ::Papaya::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PAPAYA_WARN(...) ::Papaya::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PAPAYA_ERROR(...) ::Papaya::Log::GetClientLogger()->error(__VA_ARGS__)
#define PAPAYA_FATAL(...) ::Papaya::Log::GetClientLogger()->fatal(__VA_ARGS__)

#define PAPAYA_ASSERT(x, msg)                                                        \
  if (!x)                                                                            \
  {                                                                                  \
    PAPAYA_CORE_ERROR(msg); \
  }

#else

#define PAPAYA_CORE_INFO(...)
#define PAPAYA_CORE_TRACE(...)
#define PAPAYA_CORE_WARN(...)
#define PAPAYA_CORE_ERROR(...)
#define PAPAYA_CORE_FATAL(...)

#define PAPAYA_INFO(...)
#define PAPAYA_TRACE(...)
#define PAPAYA_WARN(...)
#define PAPAYA_ERROR(...)
#define PAPAYA_FATAL(...)

#define PAPAYA_ASSERT(x, msg)

#endif

} // namespace Papaya
