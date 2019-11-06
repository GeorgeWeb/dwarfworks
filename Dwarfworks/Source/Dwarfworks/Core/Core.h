#ifndef CORE_CORE_H_
#define CORE_CORE_H_

#include <memory>
#include <utility>

// cross-platform break into the debugger, programmatically
#include "debugbreak.h"

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#ifdef _WIN64
/* Windows x64  */
#define DW_PLATFORM_WINDOWS
#else
/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define DW_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define DW_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
#define DW_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define DW_PLATFORM_LINUX
#else
/* Unknown compiler/platform */
#error "Unknown platform!"
#endif  // End of platform detection

// DLL support
#ifdef DW_PLATFORM_WINDOWS
#if DW_DYNAMIC_LINK
#ifdef DW_BUILD_DLL
#define DW_API __declspec(dllexport)
#else
#define DW_API __declspec(dllimport)
#endif
#else
#define DW_API
#endif
#elif defined(DW_PLATFORM_LINUX)
#if DW_DYNAMIC_LINK
#ifdef DW_BUILD_DLL
#define DW_API __attribute__((visibility("default")))
#else
#define DW_API
#endif
#else
#define DW_API
#endif
#else
#error Unsupported platform!
#endif  // End of DLL support

#ifdef DW_DEBUG
#define DW_ENABLE_ASSERTS
#endif

#ifdef DW_ENABLE_ASSERTS

/// \def DW_ASSERT(x, ...)
///
/// \brief A macro that defines assert.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param x   A void to process.
/// \param ... Variable arguments providing additional information.

#define DW_ASSERT(x, ...)                             \
  {                                                   \
    if (!(x)) {                                       \
      DW_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      debug_break();                                  \
    }                                                 \
  }

/// \def DW_CORE_ASSERT(x, ...)
///
/// \brief A macro that defines core assert.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param x   A void to process.
/// \param ... Variable arguments providing additional information.

#define DW_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!(x)) {                                            \
      DW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      debug_break();                                       \
    }                                                      \
  }
#else
#define DW_ASSERT(x, ...)
#define DW_CORE_ASSERT(x, ...)
#endif

/// \def BIT(x)
///
/// \brief A macro that defines bit.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param x A void to process.

#define BIT(x) (1 << x)

/// \def DW_BIND_EVENT_FN(fn)
///
/// \brief A macro that defines bind event Function.
///
/// \author Georg
/// \date 07/10/2019
///
/// \param fn The function.

#define DW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Dwarfworks {

/// \struct CRTP
///
/// \brief Curiously Recurring Template Pattern helper api. Helps getting
/// rid of `static_cast` in our CRTP interfaces
///
/// \author Georg
/// \date 07/10/2019
///
/// \typeparam ImplType Type of the implementation type.

template <typename ImplType>
struct DW_API CRTP {
  /// \fn inline ImplType& Implementation()
  ///
  /// \brief Gets the implementation.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A reference to an ImplType.

  inline ImplType& Implementation() { return static_cast<ImplType&>(*this); }

  /// \fn inline ImplType const& Implementation() const
  ///
  /// \brief Gets the implementation. Deals with the case where the
  /// implementation object is const.
  ///
  /// \author Georg
  /// \date 07/10/2019
  ///
  /// \returns A reference to a const ImplType.

  inline ImplType const& Implementation() const {
    return static_cast<ImplType const&>(*this);
  }
};

/// \brief A scoped life-time pointer (std::unique_ptr)
template <typename T>
using Scope = std::unique_ptr<T>;

/// \fn template <typename T, typename... Params> constexpr Scope<T>
/// CreateScope(Params&&... params)
///
/// \brief Creates a scope
///
/// \tparam T	   Generic type parameter.
/// \tparam Params Type of the parameters.
/// \param params A variable-length parameters list containing parameters.
///
/// \returns The new scope.

template <typename T, typename... Params>
constexpr Scope<T> CreateScope(Params&&... params) {
  return std::make_unique<T>(std::forward<Params>(params)...);
}

/// \brief A reference counting based life-time pointer (std::shared_ptr)
template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Params>

/// \fn constexpr Ref<T> CreateRef(Params&&... params)
///
/// \brief Creates a reference
///
/// \author Georg
/// \date 07/10/2019
///
/// \param params A variable-length parameters list containing parameters.
///
/// \returns The new reference.

constexpr Ref<T> CreateRef(Params&&... params) {
  return std::make_shared<T>(std::forward<Params>(params)...);
}

}  // namespace Dwarfworks

#endif  // CORE_CORE_H_
