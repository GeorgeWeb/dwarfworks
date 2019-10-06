#ifndef CORE_LOGGING_LOG_H_
#define CORE_LOGGING_LOG_H_

#include "../Core.h"

#include "spdlog/spdlog.h"
// for outputting custom types
#include "spdlog/fmt/ostr.h"

namespace Dwarfworks {
namespace Core {

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
  DW_API static void Initialize() noexcept;

  // gets the core/engine logger instance
  DW_API static inline std::shared_ptr<spdlog::logger>&
  GetCoreLogger() noexcept {
    return s_CoreLogger;
  }
  // gets the client/application logger instance
  DW_API static inline std::shared_ptr<spdlog::logger>&
  GetClientLogger() noexcept {
    return s_ClientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace Core
}  // namespace Dwarfworks

namespace {

// Core: Dwarfworks/Engine log macros
#define DW_CORE_TRACE(...) \
  ::Dwarfworks::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DW_CORE_INFO(...) \
  ::Dwarfworks::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DW_CORE_WARN(...) \
  ::Dwarfworks::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DW_CORE_ERROR(...) \
  ::Dwarfworks::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DW_CORE_FATAL(...) \
  ::Dwarfworks::Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client: Application/Game log macros
#define DW_TRACE(...) \
  ::Dwarfworks::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DW_INFO(...) \
  ::Dwarfworks::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define DW_WARN(...) \
  ::Dwarfworks::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DW_ERROR(...) \
  ::Dwarfworks::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define DW_FATAL(...) \
  ::Dwarfworks::Core::Log::GetClientLogger()->critical(__VA_ARGS__)

// Strip out (from binary) the core log macros on distribution
#ifdef DW_DIST_BUILD
#define DW_CORE_TRACE
#define DW_CORE_INFO
#define DW_CORE_WARN
#define DW_CORE_ERROR
#define DW_CORE_FATAL
#endif

}  // namespace

#endif  // CORE_LOGGING_LOG_H_
