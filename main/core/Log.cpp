#include "Log.h"

#pragma warning(push, 0)
#include "spdlog/sinks/stdout_color_sinks.h"
//#include "spdlog/sinks/ostream_sink.h" // TODO: In release and dist builds for the editor we can log into an ImGui window!
#pragma warning(pop)

namespace Papaya
{

  Ref<spdlog::logger> Log::s_CoreLogger;
  Ref<spdlog::logger> Log::s_ClientLogger;

  void Log::OnInit()
  {
    spdlog::set_pattern("%^[%T] %n: %v%s");

    s_CoreLogger = spdlog::stdout_color_mt("PAPAYA");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
  }

} // namespace Papaya
