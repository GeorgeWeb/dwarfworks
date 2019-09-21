#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Dwarfworks {
namespace Core {

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Initialize() noexcept {
  // define the log pattern:
  // appropirate color, timestamp, logger name (core/client), log message
  spdlog::set_pattern("%^[%T] %n: %v%$");

  // setup the core/engine logger object
  s_CoreLogger = spdlog::stdout_color_mt("Dwarfworks");
  s_CoreLogger->set_level(spdlog::level::trace);

  // setup the client/application logger object
  s_ClientLogger = spdlog::stdout_color_mt("Application");
  s_ClientLogger->set_level(spdlog::level::trace);
}

}  // namespace Core
}  // namespace Dwarfworks
