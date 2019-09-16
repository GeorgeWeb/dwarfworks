#ifndef DWARFWORKS_CORE_H_
#define DWARFWORKS_CORE_H_

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

#define BIT(x) (1 << x)

#endif  // DWARFWORKS_CORE_H_
