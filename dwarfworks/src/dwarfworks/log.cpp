#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace dwarfworks {

/**
 * TODO: Refactor by removing these definitions.
 * Already defined in the Translation Unit from the header,
 * (outside the log class) that gets called by a .cpp.
 */
// std::shared_ptr<spdlog::logger> log::s_coreLogger;
// std::shared_ptr<spdlog::logger> log::s_clientLogger;

void log::init() {
  // define the log pattern:
  // appropirate color, timestamp, logger name (core/client), log message
  spdlog::set_pattern("%^[%T] %n: %v%$");

  // setup the core/engine logger object
  s_coreLogger = spdlog::stdout_color_mt("Dwarfworks");
  s_coreLogger->set_level(spdlog::level::trace);

  // setup the client/application logger object
  s_clientLogger = spdlog::stdout_color_mt("Application");
  s_clientLogger->set_level(spdlog::level::trace);
}

}  // namespace dwarfworks
