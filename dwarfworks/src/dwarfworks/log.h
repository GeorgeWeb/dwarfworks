#ifndef DWARFWORKS_LOG_H_
#define DWARFWORKS_LOG_H_

#include "core.h"

// header-only (interface) lib
#include "spdlog/spdlog.h"

#include <memory>

namespace dwarfworks {

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
// functions. The private members should not be visible in the client code using
// the DLL.
//
// reference:
// https://docs.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes

class log {
 public:
  static DWARF_API void init();

  // gets the core/engine logger instance
  static DWARF_API inline std::shared_ptr<spdlog::logger>& get_core_logger() {
    return s_coreLogger;
  }
  // gets the client/application logger instance
  static DWARF_API inline std::shared_ptr<spdlog::logger>& get_client_logger() {
    return s_clientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_coreLogger;
  static std::shared_ptr<spdlog::logger> s_clientLogger;
};

}  // namespace dwarfworks

namespace {

// Core: Dwarfworks/Engine log macros
#define DWARF_CORE_TRACE(...) \
  ::dwarfworks::log::get_core_logger()->trace(__VA_ARGS__)
#define DWARF_CORE_INFO(...) \
  ::dwarfworks::log::get_core_logger()->info(__VA_ARGS__)
#define DWARF_CORE_WARN(...) \
  ::dwarfworks::log::get_core_logger()->warn(__VA_ARGS__)
#define DWARF_CORE_ERROR(...) \
  ::dwarfworks::log::get_core_logger()->error(__VA_ARGS__)
#define DWARF_CORE_FATAL(...) \
  ::dwarfworks::log::get_core_logger()->critical(__VA_ARGS__)

// Client: Application/Game log macros
#define DWARF_TRACE(...) \
  ::dwarfworks::log::get_client_logger()->trace(__VA_ARGS__)
#define DWARF_INFO(...) \
  ::dwarfworks::log::get_client_logger()->info(__VA_ARGS__)
#define DWARF_WARN(...) \
  ::dwarfworks::log::get_client_logger()->warn(__VA_ARGS__)
#define DWARF_ERROR(...) \
  ::dwarfworks::log::get_client_logger()->error(__VA_ARGS__)
#define DWARF_FATAL(...) \
  ::dwarfworks::log::get_client_logger()->critical(__VA_ARGS__)

// Strip out (from binary) the core log macros on distribution
#ifdef DWARF_DIST_BUILD
#define DWARF_CORE_TRACE
#define DWARF_CORE_INFO
#define DWARF_CORE_WARN
#define DWARF_CORE_ERROR
#define DWARF_CORE_FATAL
#endif

}  // namespace

#endif  // DWARFWORKS_LOG_H_
