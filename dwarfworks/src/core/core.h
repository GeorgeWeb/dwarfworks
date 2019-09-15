#ifndef DWARFWORKS_CORE_CORE_H_
#define DWARFWORKS_CORE_CORE_H_

#ifdef DWARFWORKS_PLATFORM_WINDOWS
	#ifdef DWARFWORKS_BUILD_DLL
	#define DWARFWORKS_API __declspec(dllexport)
	#else
	#define DWARFWORKS_API __declspec(dllimport)
	#endif // DWARFWORKS_BUILD_DLL
#else
	#error Dwarfworks only supports Windows at this stage!
#endif // DWARFWORKS_PLATFORM_WINDOWS

#endif // DWARFWORKS_CORE_CORE_H_
