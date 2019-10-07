#ifndef CORE_CORE_H_
#define CORE_CORE_H_

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
#error "Linux is not supported!"
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
#else
#error Hazel only supports Windows!
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
      __debugbreak();                                 \
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
      __debugbreak();                                      \
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

/// \def DW_FIND(cont, el)
///
/// \brief A macro that defines find
///
/// \author Georg
/// \date 07/10/2019
///
/// \param cont The container.
/// \param el   The el.

#define DW_FIND(cont, el) std::find(cont.begin(), cont.end(), el)

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

}  // namespace Dwarfworks

#endif  // CORE_CORE_H_
