#ifndef DWARFWORKS_LOG_H_
#define DWARFWORKS_LOG_H_

#include "core.h"

// header-only (interface) lib
#include "spdlog/spdlog.h"

#include <memory>

namespace dwarfworks {

class DWARFWORKS_API log {
 public:
  static void init();

  // gets the core/engine logger instance
  static std::shared_ptr<spdlog::logger>& get_core_logger() {
    return log::s_coreLogger;
  }
  // gets the client/application logger instance
  static std::shared_ptr<spdlog::logger>& get_client_logger() {
    return log::s_clientLogger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_coreLogger;
  static std::shared_ptr<spdlog::logger> s_clientLogger;
};

std::shared_ptr<spdlog::logger> log::s_coreLogger;
std::shared_ptr<spdlog::logger> log::s_clientLogger;

}  // namespace dwarfworks

#endif  // DWARFWORKS_LOG_H_
