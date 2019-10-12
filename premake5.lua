workspace "Dwarfworks"
    architecture "x64"
    configurations {
        "Debug",      -- Full on debug code enabled with all information available
        "Release",    -- Stripped out a lot of debug info, but some (like Logging) is kept
        "Dist"        -- build to be distributed to the public with all debug info stripped
    }
    startproject "Sandbox"

-- platform-independent output directory definition
OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Dwarfworks/Vendor/glfw/include"
IncludeDir["Glad"] = "Dwarfworks/Vendor/glad/include"
IncludeDir["ImGui"] = "Dwarfworks/Vendor/imgui"
IncludeDir["glm"] = "Dwarfworks/Vendor/glm"

-- define project external dependencies
group "Dependencies"
    include "Dwarfworks/Vendor/glfw"
    include "Dwarfworks/Vendor/glad"
    include "Dwarfworks/Vendor/imgui"

-- relative path to Dwarfworks source folder
local SourceDir = "%{prj.name}/Source"

----------------------------
--       Dwarfworks       --
----------------------------

project "Dwarfworks"
    -- set project general settings
    location "Dwarfworks"
    kind "StaticLib" -- SharedLib
    language "C++"
    cppdialect "C++17"
    staticruntime "on" -- off

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    pchheader "dwpch.h"                         -- create pre-compiled header
    pchsource "Dwarfworks/Source/dwpch.cpp"     -- use pre-compiled header (from source)

    -- set project source files
    files {
        -- ---------------
        -- Dwarfworks root
        -- ---------------
        SourceDir .. "/**.h",
        SourceDir .. "/**.cpp",
        -- -----------
        -- Core module
        -- -----------
        SourceDir .. "/Core/**.h",
        SourceDir .. "/Core/**.cpp",
        -- Logging sub-module
        SourceDir .. "/Core/Log/**.h",
        SourceDir .. "/Core/Log/**.cpp",
        -- Events (Event System) sub-module
        SourceDir .. "/Core/Events/**.h",
        SourceDir .. "/Core/Events/**.cpp",
        -- Application sub-module
        SourceDir .. "/Core/Application/**.h",
        SourceDir .. "/Core/Application/**.cpp",
        -- Window sub-module
        SourceDir .. "/Core/Window/**.h",
        SourceDir .. "/Core/Window/**.cpp",
        -- Layers sub-module
        SourceDir .. "/Core/Layers/**.h",
        SourceDir .. "/Core/Layers/**.cpp",
        -- DebugUI Layer
        SourceDir .. "/DebugUI/**.h",
        SourceDir .. "/DebugUI/**.cpp",
        -- ---------------
        -- Graphics module
        -- ---------------
        SourceDir .. "/Graphics/**.h",
        SourceDir .. "/Graphics/**.cpp",
        -- -----------
        -- Math module
        -- -----------
        SourceDir .. "/Math/**.h",
        SourceDir .. "/Math/**.cpp",
        -- ----------------------
        -- Platform-specific code
        -- ----------------------
        SourceDir .. "/Platform/**.h",
        SourceDir .. "/Platform/**.cpp",
        -- OpenGL
        -- SourceDir .. "/Platform/OpenGL/**.h",
        -- SourceDir .. "/Platform/OpenGL/**.cpp",
        -- Windows Window 
        SourceDir .. "/Platform/Windows/**.h",
        SourceDir .. "/Platform/Windows/**.cpp"
    }

    -- set project include directories
    includedirs {
        -- the project source folder
        SourceDir,
        -- External Logging lib - spdlog
        "%{prj.name}/Vendor/spdlog/include",
        -- (cross-platform) Window lib - GLFW
        "%{IncludeDir.GLFW}",
        -- Modern OpenGL profile loader
        "%{IncludeDir.Glad}",
        -- Immediate mode UI
        "%{IncludeDir.ImGui}",
        -- SIMD Mathematics
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    -- set project target properties
    filter "system:windows"
        systemversion "latest"

        -- preprocessor definitions
        defines {
            -- silence external "noise"
            "_CRT_SECURE_NO_WARNINGS",
            -- "DW_DYNAMIC_LINK",
            -- "DW_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        -- copying DLLs and resoruces
        -- postbuildcommands {
            -- copy dwarfworks.dll into sandbox
            -- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")
        -- }

    print("%{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")

    -- specify build and compilation options per build configuration
    filter "configurations:Debug"
        defines "DW_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "DW_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "DW_DIST"
        optimize "on"

-------------------------
--       Sandbox       --
-------------------------

project "Sandbox"
    -- set project general settings
    location "Sandbox"
    kind "ConsoleApp" -- executable
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    -- set project source files
    files {
        SourceDir .. "/**.h", -- if needed, add `.hpp` files as well
        SourceDir .. "/**.cpp"
    }

    -- set project include directories
    includedirs {
        -- The Game Engine - Dwarfworks
        "Dwarfworks/Source",
        "Dwarfworks/Vendor",
        -- External Logging lib - spdlog
        "Dwarfworks/Vendor/spdlog/include",
        -- External Mathematics lib - glm
        "Dwarfworks/Vendor/glm"
    }

    -- set project link targets
    links {
        "Dwarfworks"
    }

    -- set project target properties
    filter "system:windows"
        systemversion "latest"

        -- preprocessor definitions
        defines {
            -- "DW_DYNAMIC_LINK"
        }

    -- specify build and compilation options per build configuration
    filter "configurations:Debug"
        defines "DW_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "DW_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "DW_DIST"
        optimize "on"
