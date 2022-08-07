set(BUILD_SHARED_LIBS
    OFF
    CACHE BOOL "Add description" FORCE)
set(BUILD_STATIC_LIBS
    ON
    CACHE BOOL "Add description" FORCE)

# debugbreak
add_library(debugbreak INTERFACE
            "${Dwarfworks_Vendor_Dir}/debugbreak/debugbreak.h")

# spdlog
add_subdirectory(spdlog)
# already has an Alias spdlog::spdlog

# glm
set(GLM_TEST_ENABLE
    OFF
    CACHE BOOL "Add description")
add_subdirectory(glm)
add_library(glm::glm ALIAS glm_static)

# glfw
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "Add description" FORCE)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "Add description" FORCE)
set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "Add description" FORCE)
set(GLFW_INSTALL
    OFF
    CACHE BOOL "Add description" FORCE)
#
if (MSVC)
    # TODO(georgi) find the respective code for the warning
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wobjc-multiple-method-names)
endif()
add_subdirectory(glfw)

# glad
add_subdirectory(glad)

# ImGui
add_subdirectory(ImGui)

# stb_image
add_subdirectory(stb_image)
