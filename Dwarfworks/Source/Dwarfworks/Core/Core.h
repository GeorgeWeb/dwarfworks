#ifndef CORE_CORE_H
#define CORE_CORE_H

#include <cstdint>
#include <memory>
#include <utility>

#include "CompilerWarningsHelper.h"

// Cross-platform break into the debugger, programmatically
// NOTE: We are suppressing warnings in debugbreak for now.
// TODO(georgi): Fix the code producing them in debugbreak!
DISABLE_WARNING_PUSH
DISABLE_WARNING_WITHOUT_EXTERN
#include "debugbreak.h"
DISABLE_WARNING_POP

// --------------------------------------- //
// PLATFORM
// --------------------------------------- //

// Platform detection using predefined macros
#ifdef _WIN32
    /* Windows x64/x86 */
    #ifdef _WIN64
        /* Windows x64  */
        #ifndef PLATFORM_WINDOWS
            #define PLATFORM_WINDOWS 1
        #endif
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
        #ifndef PLATFORM_IOS
            #define PLATFORM_IOS 1
        #endif
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #ifndef PLATFORM_MACOS
            #define PLATFORM_MACOS 1
        #endif
        // #warning "MacOS is experimentally supported!"
    #else
        #error "Unknown Apple platform!"
    #endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
    #ifndef PLATFORM_ANDROID
        #define PLATFORM_ANDROID 1
    #endif
    #error "Android is not supported!"
#elif defined(__linux__)
    #ifndef PLATFORM_LINUX
        #define PLATFORM_LINUX 1
    #endif
    #error "Linux is not supported yet!"
#else
    /* Unknown compiler/platform */
    #error "Unknown platform!"
#endif // End of platform detection

// Support for building Dwarfworks as SharedLib/DLL
#ifdef PLATFORM_WINDOWS
    #if DYNAMIC_LINK
        #ifdef BUILD_DLL
            #pragma message("Exporting...")
            #define ENGINE_API __declspec(dllexport)
        #else
            #pragma message("Importing...")
            #define ENGINE_API __declspec(dllimport)
        #endif
    #else
        #define ENGINE_API
    #endif
#elif defined(PLATFORM_LINUX)
    #if DYNAMIC_LINK
        #ifdef BUILD_DLL
            #define ENGINE_API __attribute__((visibility("default")))
        #else
            #define ENGINE_API
        #endif
    #else
        #define ENGINE_API
    #endif
#elif defined(PLATFORM_MACOS)
    #if DYNAMIC_LINK
        #ifdef BUILD_DLL
            #define ENGINE_API __attribute__((visibility("default")))
        #else
            #define ENGINE_API
        #endif
    #else
        #define ENGINE_API
    #endif
#else
    #error Unsupported platform!
#endif // End of DLL support

// Debug function macros

#ifdef DW_DEBUG
    #define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
    #define DW_ASSERT(x, ...)                                                                                          \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                DW_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                        \
                debug_break();                                                                                         \
            }                                                                                                          \
        }

    #define DW_CORE_ASSERT(x, ...)                                                                                     \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                DW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                   \
                debug_break();                                                                                         \
            }                                                                                                          \
        }
#else
    #define DW_ASSERT(x, ...)
    #define DW_CORE_ASSERT(x, ...)
#endif

// --------------------------------------- //
// TYPES
// --------------------------------------- //

typedef uint32_t uint32;
typedef int32_t  int32;
typedef int8_t   int8;
typedef uint8_t  uint8;
typedef uint8    byte;

// --------------------------------------- //
// GENERIC / HELPERS
// --------------------------------------- //

#define BIT(x) (1 << x)

// TODO(georgi): Think about getting rid of the macro and making it a template generic function!
// Also, rename to BIND_MEMBER_FUNCTION as we'll have 'BIND_FUNCTION' and 'BIND_STATIC_FUNCTION'
#define BIND_MEMBER(fn)                                                                                                \
    [this](auto&&... args) -> decltype(auto) {                                                                         \
        return this->fn(std::forward<decltype(args)>(args)...);                                                        \
    }

#define ARRAY_COUNT(arr) (uint32)(sizeof(arr) / sizeof(arr[0]))

namespace Dwarfworks
{
/**
 * @brief
 *
 */
class ENGINE_API Noncopyable
{
  protected:
    Noncopyable()          = default;
    virtual ~Noncopyable() = default;
    // Delete copy constructor & assignment operator
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
    // Leave default implementations of the move constructor & assignment operator
    // the derived classes can specialize them where needed.
    Noncopyable(Noncopyable&&) noexcept = default;
    Noncopyable& operator=(Noncopyable&&) noexcept = default;
};

/**
 * @brief
 *
 */
class ENGINE_API Nonmoveable
{
  protected:
    Nonmoveable()          = default;
    virtual ~Nonmoveable() = default;
    // Delete move constructor & assignment operator
    Nonmoveable(Nonmoveable&&) noexcept = delete;
    Nonmoveable& operator=(Nonmoveable&&) noexcept = delete;
    // Leave default implementations of the copy constructor & assignment operator
    // the derived classes can specialize them where needed.
    Nonmoveable(const Nonmoveable&) = default;
    Nonmoveable& operator=(const Nonmoveable&) = default;
};

/**
 * @brief Curiously Recurring Template Pattern helper API.
 * Helps getting rid of _static_cast_s in CRTP interfaces.
 */
template <class Impl>
class ENGINE_API CRTP
{
  public:
    inline Impl&       Implementation() { return static_cast<Impl&>(*this); }
    inline const Impl& Implementation() const { return static_cast<const Impl&>(*this); }
};

template <class T>
using Scope = std::unique_ptr<T>;

/**
 * @brief Create a Scope object
 *
 * @tparam T
 * @tparam Args
 * @param args
 * @return ENGINE_API constexpr Scope<T>
 */
template <class T, class... Args>
ENGINE_API static constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <class T>
using Ref = std::shared_ptr<T>;

/**
 * @brief Create a Ref object
 *
 * @tparam T
 * @tparam Args
 * @param args
 * @return constexpr Ref<T>
 */
template <class T, class... Args>
ENGINE_API static constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace Dwarfworks

#endif // CORE_CORE_H
