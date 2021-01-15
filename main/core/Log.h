#ifndef Log_h
#define Log_h

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Papaya
{

class Log {
public:
  static void OnInit();

  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
  inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

#ifdef PAPAYA_DEBUG

#define PAPAYA_CORE_INFO(...)    ::Papaya::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PAPAYA_CORE_TRACE(...)   ::Papaya::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PAPAYA_CORE_WARN(...)    ::Papaya::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PAPAYA_CORE_ERROR(...)   ::Papaya::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PAPAYA_CORE_FATAL(...)   ::Papaya::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define PAPAYA_INFO(...)         ::Papaya::Log::GetClientLogger()->info(__VA_ARGS__)
#define PAPAYA_TRACE(...)        ::Papaya::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PAPAYA_WARN(...)         ::Papaya::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PAPAYA_ERROR(...)        ::Papaya::Log::GetClientLogger()->error(__VA_ARGS__)
#define PAPAYA_FATAL(...)        ::Papaya::Log::GetClientLogger()->fatal(__VA_ARGS__)

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

#endif

} // namespace Papaya


#endif /* end of include guard: Log_h */
