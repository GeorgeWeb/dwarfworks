#ifndef DWARFWORKS_LOG_H_
#define DWARFWORKS_LOG_H_

#include "core.h"

// header-only (interface) lib
#include "spdlog/spdlog.h"

#include <memory>

namespace dwarfworks {

class DWARF_API log {
 public:
  static void init();

  // gets the core/engine logger instance
  static inline std::shared_ptr<spdlog::logger>& get_core_logger() {
    return s_coreLogger;
  }
  // gets the client/application logger instance
  static inline std::shared_ptr<spdlog::logger>& get_client_logger() {
    return s_clientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_coreLogger;
  static std::shared_ptr<spdlog::logger> s_clientLogger;
};

// std::shared_ptr<spdlog::logger> log::s_coreLogger;
// std::shared_ptr<spdlog::logger> log::s_clientLogger;

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
