#ifndef CORE_LOGGING_LOG_H_
#define CORE_LOGGING_LOG_H_

#include "../Core.h"

#include "spdlog/spdlog.h"
// for outputting custom types
#include "spdlog/fmt/ostr.h"

namespace Dwarfworks {

// -------------------------------------------------------------------------------------
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
// -------------------------------------------------------------------------------------

/// \class Log
///
/// \brief A log.
///
/// \author Georg
/// \date 07/10/2019

class Log {
 public:
  /// \fn DW_API static void Log::Initialize() noexcept;
  ///
  /// \brief Initializes this object.
  ///
  /// \author Georg
  /// \date 07/10/2019

  DW_API static void Initialize() noexcept;

  /// \fn DW_API static inline std::shared_ptr<spdlog::logger>&
  /// Log::GetCoreLogger() noexcept
  ///
  /// \brief Gets core logger.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The core logger.

  DW_API static inline std::shared_ptr<spdlog::logger>&
  GetCoreLogger() noexcept {
    return s_CoreLogger;
  }

  /// \fn DW_API static inline std::shared_ptr<spdlog::logger>&
  /// Log::GetClientLogger() noexcept
  ///
  /// \brief Gets client logger.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns The client logger.

  DW_API static inline std::shared_ptr<spdlog::logger>&
  GetClientLogger() noexcept {
    return s_ClientLogger;
  }

 private:
  /// \brief The core logger.
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  /// \brief The client logger.
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace Dwarfworks

// Core: Dwarfworks/Engine log macros

/// \def DW_CORE_TRACE(...)
///
/// \brief A macro that defines core trace.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_CORE_TRACE(...) \
  ::Dwarfworks::Log::GetCoreLogger()->trace(__VA_ARGS__)

/// \def DW_CORE_INFO(...)
///
/// \brief A macro that defines core Information.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_CORE_INFO(...) ::Dwarfworks::Log::GetCoreLogger()->info(__VA_ARGS__)

/// \def DW_CORE_WARN(...)
///
/// \brief A macro that defines core Warning.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_CORE_WARN(...) ::Dwarfworks::Log::GetCoreLogger()->warn(__VA_ARGS__)

/// \def DW_CORE_ERROR(...)
///
/// \brief A macro that defines core error.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_CORE_ERROR(...) \
  ::Dwarfworks::Log::GetCoreLogger()->error(__VA_ARGS__)

/// \def DW_CORE_FATAL(...)
///
/// \brief A macro that defines core fatal.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_CORE_FATAL(...) \
  ::Dwarfworks::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client: Application/Game log macros

/// \def DW_TRACE(...)
///
/// \brief A macro that defines trace.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_TRACE(...) ::Dwarfworks::Log::GetClientLogger()->trace(__VA_ARGS__)

/// \def DW_INFO(...)
///
/// \brief A macro that defines Information.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_INFO(...) ::Dwarfworks::Log::GetClientLogger()->info(__VA_ARGS__)

/// \def DW_WARN(...)
///
/// \brief A macro that defines Warning.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_WARN(...) ::Dwarfworks::Log::GetClientLogger()->warn(__VA_ARGS__)

/// \def DW_ERROR(...)
///
/// \brief A macro that defines error.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_ERROR(...) ::Dwarfworks::Log::GetClientLogger()->error(__VA_ARGS__)

/// \def DW_FATAL(...)
///
/// \brief A macro that defines fatal.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param ... Variable arguments providing additional information.

#define DW_FATAL(...) \
  ::Dwarfworks::Log::GetClientLogger()->critical(__VA_ARGS__)

// Strip out (from binary) the core log macros on distribution
#ifdef DW_DIST_BUILD
#define DW_CORE_TRACE
#define DW_CORE_INFO
#define DW_CORE_WARN
#define DW_CORE_ERROR
#define DW_CORE_FATAL
#endif

#endif  // CORE_LOGGING_LOG_H_
