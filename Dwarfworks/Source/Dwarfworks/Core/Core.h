#ifndef CORE_CORE_H_
#define CORE_CORE_H_

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
#error Dwarfworks only supports Windows at the time!
#endif

// used to create bitfields
#define BIT(x) (1 << x)

namespace Dwarfworks {
namespace Core {

// Helps getting rid of `static_cast` in our CRTP interfaces
template <typename ImplType>
struct DW_API CRTP {
  inline ImplType& Implementation() { return static_cast<ImplType&>(*this); }
  // Deals with the case where the implementation object is const
  inline ImplType const& Implementation() const {
    return static_cast<ImplType const&>(*this);
  }
};

}  // namespace Core
}  // namespace Dwarfworks

#endif  // CORE_CORE_H_
