#include "Log.h"

#pragma warning(push, 0)
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ostream_sink.h"
#pragma warning(pop)

namespace Papaya
{

  Ref<spdlog::logger> Log::s_CoreLogger;
  Ref<spdlog::logger> Log::s_ClientLogger;

  std::ostringstream Log::s_CoreStream;
  std::ostringstream Log::s_ClientStream;

  void Log::OnInit()
  {
    const char* formatString = "[%T] %n: %^%v%$ %s";

    Ref<spdlog::sinks::stdout_color_sink_mt> coreConsoleSink = CreateRef<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::always);
    Ref<spdlog::sinks::stdout_color_sink_mt> clientConsoleSink = CreateRef<spdlog::sinks::stdout_color_sink_mt>(spdlog::color_mode::always);

    Ref<spdlog::sinks::ostream_sink_mt> coreStreamSink = CreateRef<spdlog::sinks::ostream_sink_mt>(s_CoreStream, true);
    Ref<spdlog::sinks::ostream_sink_mt> clientStreamSink = CreateRef<spdlog::sinks::ostream_sink_mt>(s_ClientStream, true);

    s_CoreLogger = CreateRef<spdlog::logger>("PAPAYA", spdlog::sinks_init_list({ coreConsoleSink, coreStreamSink }));
    s_CoreLogger->set_pattern(formatString);
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = CreateRef<spdlog::logger>("PAPAYA", spdlog::sinks_init_list({ clientConsoleSink, clientStreamSink }));
    s_ClientLogger->set_pattern(formatString);
    s_ClientLogger->set_level(spdlog::level::trace);

  }

} // namespace Papaya
