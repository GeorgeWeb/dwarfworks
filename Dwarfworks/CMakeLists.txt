# Dwarfworks source directory
set(Dwarfworks_Source_Dir
    "${Dwarfworks_Dir}/Source"
    CACHE PATH "")
# Dwarfworks vendor directory
set(Dwarfworks_Vendor_Dir
    "${Dwarfworks_Dir}/Vendor"
    CACHE PATH "")

# Dwarfworks source files
list(
  APPEND
  Dwarfworks_Sources
  # Engine module
  # -------------
  # Core
  "${Dwarfworks_Source_Dir}/Dwarfworks/Core/Core.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Core/Log/Log.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Core/Layer/Layer.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Core/Layer/LayerStack.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Core/Window/Window.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Core/Application/Application.cpp"
  # Events
  "${Dwarfworks_Source_Dir}/Dwarfworks/Event/Event.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Event/ApplicationEvent.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Event/MouseEvent.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Event/KeyEvent.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Event/EventManager.cpp"
  # (Vector) Math
  "${Dwarfworks_Source_Dir}/Dwarfworks/Math/Math.cpp"
  # Renderer
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/GraphicsContext.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/Adapter.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/Buffer.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/VertexArray.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/Shader.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/Texture.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/RendererAPI.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/RenderCommand.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/Renderer.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/2D/Renderer2D.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/Camera.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/Renderer/CameraController.cpp"
  # ImGui
  "${Dwarfworks_Source_Dir}/Dwarfworks/DebugUI/DebugUIBuild.cpp"
  "${Dwarfworks_Source_Dir}/Dwarfworks/DebugUI/DebugUILayer.cpp"
  # Platform module
  # ---------------
  # OpenGL
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLLoader.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLDriver.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLContext.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLAdapter.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLBuffer.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLRendererAPI.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLShader.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLTexture.cpp"
  "${Dwarfworks_Source_Dir}/Platform/OpenGL/OpenGLVertexArray.cpp")

# Add platform-specific sources
if(PLATFORM_WINDOWS)
  list(
    APPEND
    Dwarfworks_Sources
    # Windows
    "${Dwarfworks_Source_Dir}/Platform/Windows/WindowsInput.cpp"
    "${Dwarfworks_Source_Dir}/Platform/Windows/WindowsWindow.cpp")
elseif(PLATFORM_LINUX)
  list(
    APPEND
    Dwarfworks_Sources
    # Linux
    "${Dwarfworks_Source_Dir}/Platform/Linux/LinuxInput.cpp"
    "${Dwarfworks_Source_Dir}/Platform/Linux/LinuxWindow.cpp")
elseif(PLATFORM_MACOS)
  list(
    APPEND
    Dwarfworks_Sources
    # MacOS
    "${Dwarfworks_Source_Dir}/Platform/Mac/MacInput.cpp"
    "${Dwarfworks_Source_Dir}/Platform/Mac/MacWindow.cpp"
    # "${Dwarfworks_Source_Dir}/Platform/Mac/MacWindow.mm"
    "${Dwarfworks_Source_Dir}/Platform/OpenGL/Mac/MacOpenGLDriver.cpp")
endif()

# Dwarfworks include directories
list(APPEND Dwarfworks_Include_Directories_Public
     # source includes (and vendors(*) if needed)
     "${Dwarfworks_Source_Dir}" "${Dwarfworks_Vendor_Dir}")
list(
  APPEND
  Dwarfworks_Include_Directories_Internal
  "${Dwarfworks_Source_Dir}"
  "${Dwarfworks_Vendor_Dir}"
  # Cross-platform break into source-line debugger
  "${Dwarfworks_Vendor_Dir}/debugbreak"
  # Fast Logging library
  "${Dwarfworks_Vendor_Dir}/spdlog/include"
  # SIMD Mathematics
  "${Dwarfworks_Vendor_Dir}/glm"
  # Cross-platform window library
  "${Dwarfworks_Vendor_Dir}/glfw/include"
  # Modern OpenGL loader
  "${Dwarfworks_Vendor_Dir}/glad/include"
  # ImGui (immediate mode UI)
  "${Dwarfworks_Vendor_Dir}/imgui"
  # Image decoding/encoding
  "${Dwarfworks_Vendor_Dir}/stb_image")
# cache the include directories for use in applications
set(Dwarfworks_Include_Directories
    ${Dwarfworks_Include_Directories_Public}
    ${Dwarfworks_Include_Directories_Internal}
    CACHE INTERNAL "")
# debug print the includes
message(NOTICE "Dwarfworks Includes:")
message(NOTICE "${Dwarfworks_Include_Directories}")

# build vendor libraries
add_subdirectory(${Dwarfworks_Vendor_Dir})

# plan for future support of a custom non-std cmath library/functions subset.
option(USE_DWMATH "Use custom math implementation (Not implemented yet)" OFF)
# example usage:
# https://cmake.org/cmake/help/latest/guide/tutorial/Selecting%20Static%20or%20Shared%20Libraries.html

# build and link the Dwarfworks library
if(BUILD_SHARED_LIBS)
  set(Dwarfworks_Library "dwarfworks_shared")
  add_library(${Dwarfworks_Library} SHARED ${Dwarfworks_Sources})
else()
  set(Dwarfworks_Library "dwarfworks_static")
  add_library(${Dwarfworks_Library} STATIC ${Dwarfworks_Sources})
endif()

# Interprocedural (link time) optimization
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(${Dwarfworks_Library}
                        PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Setup Dwarfworks pre-compiled headers
target_precompile_headers(${Dwarfworks_Library} PRIVATE
                          "${Dwarfworks_Source_Dir}/dwpch.h")

# state that anybody linking to us needs to include the current source directory
# to find Dwarfworks.h, while we don't.
#
target_include_directories(${Dwarfworks_Library}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# project compiler options
target_link_libraries(${Dwarfworks_Library} INTERFACE project_options)

# project vendor libraries
target_link_libraries(${Dwarfworks_Library} INTERFACE debugbreak)
target_link_libraries(${Dwarfworks_Library} PRIVATE spdlog::spdlog)
target_link_libraries(${Dwarfworks_Library} PRIVATE glm::glm)
target_link_libraries(${Dwarfworks_Library} PRIVATE glfw ${GLFW_LIBRARIES})
target_link_libraries(${Dwarfworks_Library} PRIVATE glad)
target_link_libraries(${Dwarfworks_Library} PRIVATE ImGui)
target_link_libraries(${Dwarfworks_Library} PRIVATE stb_image)

# project includes
target_include_directories(${Dwarfworks_Library}
                           PUBLIC ${Dwarfworks_Include_Directories})

if(BUILD_SHARED_LIBS)
  add_library(dwarfworks::dwarfworks ALIAS dwarfworks_shared)
else()
  add_library(dwarfworks::dwarfworks ALIAS dwarfworks_static)
endif()

# TODO(georgi): handle install (, export ,) and package
