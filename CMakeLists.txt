cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
cmake_policy(VERSION 3.16)
project(
  dwarfworks
  DESCRIPTION "Dwarfworks Game Engine"
  LANGUAGES C CXX OBJC OBJCXX ASM)

message(STATUS "Building Dwarfworks...")

# Detect build (host) platform. NOTE this is incomplete.
if(WIN32) # Windows
  set(PLATFORM_WINDOWS
      True
      CACHE INTERNAL "")
  add_compile_definitions(PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE) # Linux
  set(PLATFORM_LINUX
      True
      CACHE INTERNAL "")
  add_compile_definitions(PLATFORM_LINUX)
elseif(APPLE) # MacOs
  set(PLATFORM_MACOS
      True
      CACHE INTERNAL "")
  add_compile_definitions(PLATFORM_MACOS)
else()
  message(FATAL_ERROR "Platform NOT supported!")
endif()
# Print the platform
if(PLATFORM_WINDOWS)
  message(STATUS "Platform: Windows")
elseif(PLATFORM_LINUX)
  message(STATUS "Platform: Linux")
elseif(PLATFORM_MACOS)
  message(STATUS "Platform: MacOS")
endif()

# build configuration
set(CMAKE_BUILD_TYPE
    "Debug"
    CACHE STRING "" FORCE)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions(DW_DEBUG)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(DW_RELEASE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Dist")
  add_compile_definitions(DW_DIST)
else()
  message(FATAL_ERROR "The requested build configuration is not supported")
endif()

# export compile commands for use with clang tools
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  set(CMAKE_EXPORT_COMPILE_COMMANDS
      True
      CACHE BOOL "" FORCE)
endif()

# configure a header file to pass the version number only
# configure_file(DwarfworksConfig.h.in DwarfworksConfig.h)

# control where the static and shared libraries are built so that on Windows we
# don't need to tinker with the path to run the executable
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
#
# Binaries (/Debug/Mac) ; Intermediates (/Debug/Mac)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CCache
option(ENABLE_CCACHE "Use ccache to speed up iterative builds" OFF)
if (ENABLE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

# clang-tidy
find_program(
  CLANG_TIDY_PROGRAM
  NAMES "clang-tidy"
  DOC "$(which clang-tidy)")
if(CLANG_TIDY_PROGRAM)
  message(STATUS "Found clang-tidy.")
endif()

# todo add description
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
# todo add description
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang"
         OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# build as shared library
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
# NOTE need PIC(POSITION_INDEPENDENT_CODE) with shared libs.

# user-specified option for whether to build the sandbox application
option(BUILD_SANDBOX "Build the Sandbox example of using Dwarfworks" ON)

# The default Dwarfworks root directory (keep internal for now)
set(Dwarfworks_Dir
    "${CMAKE_CURRENT_SOURCE_DIR}/Dwarfworks"
    CACHE PATH "")
# mark_as_advanced(Dwarfworks_Dir)

# The Dwarfworks include directories
set(Dwarfworks_Include_Directories_Public
    ${Dwarfworks_Dir}
    CACHE INTERNAL "")
set(Dwarfworks_Include_Directories_Internal
    ${Dwarfworks_Dir}
    CACHE INTERNAL "")

# Some IDEs, like Xcode, support folders. We nhave to manually enable the
# property to allow CMake to organize the files by folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# build Dwarfworks
if(BUILD_SHARED_LIBS)
  message(
    FATAL_ERROR "Building Dwarfworks as shared library is not supported yet.")
endif()
add_subdirectory(Dwarfworks)

# build Sandbox
if(BUILD_SANDBOX)
  add_subdirectory(Sandbox)
endif()
