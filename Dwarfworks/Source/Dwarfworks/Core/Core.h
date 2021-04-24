#ifndef CORE_CORE_H_
#define CORE_CORE_H_

#include <memory>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

// cross-platform break into the debugger, programmatically
#include <debugbreak.h>

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
#endif // End of platform detection

// DLL support
#ifdef DW_PLATFORM_WINDOWS
    #if DW_DYNAMIC_LINK
        #ifdef DW_BUILD_DLL
            #pragma message("Exporting...")
            #define ENGINE_API __declspec(dllexport)
        #else
            #pragma message("Importing...")
            #define ENGINE_API __declspec(dllimport)
        #endif
    #else
        #define ENGINE_API
    #endif
#elif defined(DW_PLATFORM_LINUX)
    #if DW_DYNAMIC_LINK
        #ifdef DW_BUILD_DLL
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
    #define DW_ENABLE_ASSERTS
#endif

#ifdef DW_ENABLE_ASSERTS
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

// Helper function macros

#define BIT(x) (1 << x)

#define DW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Helper generic/meta functions and interfaces

namespace Dwarfworks
{
class ENGINE_API Noncopyable
{
  protected:
    constexpr Noncopyable() = default;
    ~Noncopyable()          = default;
    // Delete copy constructor & assignment operator
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
    // Leave default implementations of the move constructor & assignment operator
    // the derived classes can specialize them where needed.
    Noncopyable(Noncopyable&&) = default;
    Noncopyable& operator=(Noncopyable&&) = default;
};

class ENGINE_API Nonmoveable
{
  protected:
    constexpr Nonmoveable() = default;
    ~Nonmoveable()          = default;
    // Delete move constructor & assignment operator
    Nonmoveable(Nonmoveable&&) = delete;
    Nonmoveable& operator=(Nonmoveable&&) = delete;
    // Leave default implementations of the copy constructor & assignment operator
    // the derived classes can specialize them where needed.
    Nonmoveable(const Nonmoveable&) = default;
    Nonmoveable& operator=(const Nonmoveable&) = default;
};

// Curiously Recurring Template Pattern helper api. Helps getting
// rid of `static_cast` in our CRTP interfaces
template <class ImplT>
class ENGINE_API CRTP
{
  public:
    inline ImplT&       Implementation() { return static_cast<ImplT&>(*this); }
    inline ImplT const& Implementation() const { return static_cast<ImplT const&>(*this); }
};

template <class T>
using Scope = std::unique_ptr<T>;

template <class T, class... Params>
constexpr Scope<T> CreateScope(Params&&... params)
{
    return std::make_unique<T>(std::forward<Params>(params)...);
}

template <class T>
using Ref = std::shared_ptr<T>;
template <class T, class... Params>

constexpr Ref<T> CreateRef(Params&&... params)
{
    return std::make_shared<T>(std::forward<Params>(params)...);
}

} // namespace Dwarfworks

#endif // CORE_CORE_H_
