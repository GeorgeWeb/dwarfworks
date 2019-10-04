#ifndef DWARFWORKS_CORE_CORE_H_
#define DWARFWORKS_CORE_CORE_H_

#ifdef DWARF_PLATFORM_WINDOWS
#if DWARF_DYNAMIC_LINK
#ifdef DWARF_BUILD_DLL
#define DWARF_API __declspec(dllexport)
#else
#define DWARF_API __declspec(dllimport)
#endif  // DWARF_BUILD_DLL
#else
#define DWARF_API
#endif
#else
#error Dwarfworks only supports Windows at the time!
#endif  // DWARF_PLATFORM_WINDOWS

// used to create bitfields
#define BIT(x) (1 << x)

namespace Dwarfworks {
namespace Core {

// Helps getting rid of `static_cast` in our CRTP interfaces
template <typename ImplType>
struct DWARF_API CRTP {
  inline ImplType& Implementation() { return static_cast<ImplType&>(*this); }
  // Deals with the case where the implementation object is const
  inline ImplType const& Implementation() const {
    return static_cast<ImplType const&>(*this);
  }
};

}  // namespace Core
}  // namespace Dwarfworks

#endif  // DWARFWORKS_CORE_CORE_H_
