cmake_minimum_required(VERSION 3.16)
project(
  Sandbox
  DESCRIPTION "Sandbox - example of Dwarfworks"
  LANGUAGES C CXX)

message(STATUS "Building Sandbox...")

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

# set(Dwarfworks_Dir "${CMAKE_SOURCE_DIR}" CACHE PATH "")
set(Sandbox_Dir
    "${CMAKE_CURRENT_SOURCE_DIR}"
    CACHE PATH "")
set(Sandbox_Source_Dir
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
    CACHE PATH "")

# Dwarfworks source files
list(
  APPEND
  Sandbox_Sources
  # all Sandbox (cpp) sources Sandbox Application
  "${Sandbox_Source_Dir}/Sandbox.cpp"
  # Sandbox Application Default Layer
  "${Sandbox_Source_Dir}/SandboxLayer.cpp")

add_executable(Sandbox ${Sandbox_Sources})
# link Dwarfworks
target_link_libraries(Sandbox PRIVATE dwarfworks::dwarfworks)
#
# target_link_libraries(Sandbox PRIVATE "-framework Cocoa")
# target_link_libraries(Sandbox PRIVATE "-framework OpenGL")
# target_link_libraries(Sandbox PRIVATE "-framework IOKit")

# Sandbox includes
target_include_directories(Sandbox PUBLIC ${Sandbox_Sources}
                                          ${Dwarfworks_Include_Directories})

# target_precompile_headers(Sandbox REUSE_FROM dwarfworks::dwarfworks) # reuse
# PCH
