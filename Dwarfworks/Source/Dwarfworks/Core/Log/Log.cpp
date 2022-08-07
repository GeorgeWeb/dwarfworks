// begin PCH
#include "dwpch.h"
// end PCH

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

using namespace Dwarfworks;

Ref<spdlog::logger> Log::s_CoreLogger;   // = nullptr;
Ref<spdlog::logger> Log::s_ClientLogger; // = nullptr;

void Log::Initialize(std::string_view coreLoggerName, std::string_view clientLoggerName) noexcept
{
    // define the log pattern:
    // color, timestamp, logger name (core/client), log msg
    spdlog::set_pattern("%^[%T] %n: %v%$");

    // create logger objects
    using factory  = spdlog::synchronous_factory;
    s_CoreLogger   = spdlog::stdout_color_mt<factory>(coreLoggerName.data());
    s_ClientLogger = spdlog::stdout_color_mt<factory>(clientLoggerName.data());

    // set default logging severity
    s_CoreLogger->set_level(spdlog::level::trace);
    s_ClientLogger->set_level(spdlog::level::trace);
}
