#ifndef DWARFWORKS_CORE_LOGGING_LOG_H_
#define DWARFWORKS_CORE_LOGGING_LOG_H_

#include "../Core.h"

// header-only (interface) lib
#include "spdlog/spdlog.h"

#include <memory>

namespace Dwarfworks {
namespace Core {
namespace Logging {

// Cannot export the log class symbols with `dllexport`, due to warnings:
//
// src\dwarfworks\log.h(27, 54) : warning C4251 :
// 'dwarfworks::log::s_coreLogger' : class 'std::shared_ptr<spdlog::logger>'
// needs to have dll - interface to be used by clients of class
// 'dwarfworks::log' vendor\spdlog\include\spdlog\details\registry.h(33) :
// message: see declaration of 'std::shared_ptr<spdlog::logger>'
//
// AND:
//
// src\dwarfworks\log.h(28, 56) : warning C4251 :
// 'dwarfworks::log::s_clientLogger' : class 'std::shared_ptr<spdlog::logger>'
// needs to have dll - interface to be used by clients of class
// 'dwarfworks::log' vendor\spdlog\include\spdlog\details\registry.h(33) :
// message: see declaration of 'std::shared_ptr<spdlog::logger>'
//
// Thus, adding `dllexport/dllimport` (via DWARF_API) for each of the static
// functions. The private static members are be visible in the client code
// that will be using the DLL.
//
// reference:
// https://docs.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes

class Log {
 public:
  DWARF_API static void Initialize() noexcept;

  // gets the core/engine logger instance
  DWARF_API static inline std::shared_ptr<spdlog::logger>&
  GetCoreLogger() noexcept {
    return s_CoreLogger;
  }
  // gets the client/application logger instance
  DWARF_API static inline std::shared_ptr<spdlog::logger>&
  GetClientLogger() noexcept {
    return s_ClientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace Logging
}  // namespace Core
}  // namespace Dwarfworks

namespace {

// Core: Dwarfworks/Engine log macros
#define DWARF_CORE_TRACE(...) \
  ::Dwarfworks::Core::Logging::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DWARF_CORE_INFO(...) \
  ::Dwarfworks::Core::Logging::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DWARF_CORE_WARN(...) \
  ::Dwarfworks::Core::Logging::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DWARF_CORE_ERROR(...) \
  ::Dwarfworks::Core::Logging::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DWARF_CORE_FATAL(...) \
  ::Dwarfworks::Core::Logging::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client: Application/Game log macros
#define DWARF_TRACE(...) \
  ::Dwarfworks::Core::Logging::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DWARF_INFO(...) \
  ::Dwarfworks::Core::Logging::Log::GetClientLogger()->info(__VA_ARGS__)
#define DWARF_WARN(...) \
  ::Dwarfworks::Core::Logging::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DWARF_ERROR(...) \
  ::Dwarfworks::Core::Logging::Log::GetClientLogger()->error(__VA_ARGS__)
#define DWARF_FATAL(...) \
  ::Dwarfworks::Core::Logging::Log::GetClientLogger()->critical(__VA_ARGS__)

// Strip out (from binary) the core log macros on distribution
#ifdef DWARF_DIST_BUILD
#define DWARF_CORE_TRACE
#define DWARF_CORE_INFO
#define DWARF_CORE_WARN
#define DWARF_CORE_ERROR
#define DWARF_CORE_FATAL
#endif

}  // namespace

#endif  // DWARFWORKS_CORE_LOGGING_LOG_H_
