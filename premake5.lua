workspace "Dwarfworks"
    architecture "x64"
    configurations {
        "Debug",      -- Full on debug code enabled with all information available
        "Release",    -- Stripped out a lot of debug info, but some (like Logging) is kept
        "Dist"        -- build to be distributed to the public with all debug info stripped
    }

-- platform-independent output directory definition
OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Dwarfworks/Vendor/glfw/include"

-- define project external dependencies
group "Dependencies"
    include "Dwarfworks/Vendor/glfw"

-- relative path to Dwarfworks source folder
local SourceDir = "%{prj.name}/Source"

----------------------------
--       Dwarfworks       --
----------------------------

project "Dwarfworks"
    -- set project general settings
    location "Dwarfworks"
    kind "SharedLib" -- dynamically linked library (DLL)
    language "C++"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    pchheader "dwpch.h"                         -- create pre-compiled header
    pchsource "Dwarfworks/Source/dwpch.cpp"     -- use pre-compiled header (from source)

    -- set project source files
    files {
        -- Dwarfworks root
        SourceDir .. "/**.h",
        SourceDir .. "/**.cpp",
        -- Core module
        SourceDir .. "/Core/**.h",
        SourceDir .. "/Core/**.cpp",
        --/-- Event System
        SourceDir .. "/Core/EventSystem/**.h",
        SourceDir .. "/Core/EventSystem/**.cpp",
        --/--/-- Defaut Events
        SourceDir .. "/Core/EventSystem/Events/**.h",
        SourceDir .. "/Core/EventSystem/Events/**.cpp",
        -- Graphics module
        SourceDir .. "/Graphics/**.h",
        SourceDir .. "/Graphics/**.cpp",
        -- Math module
        SourceDir .. "/Math/**.h",
        SourceDir .. "/Math/**.cpp"
    }

    -- set project include directories
    includedirs {
        -- the project source folder
        SourceDir,
        -- External Logging lib - spdlog
        "%{prj.name}/Vendor/spdlog/include",
        -- (cross-platform) Window lib - GLFW
        "%{IncludeDir.GLFW}"
    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    -- set project target properties
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        -- preprocessor definitions
        defines {
            "DW_PLATFORM_WINDOWS",
            "DW_DYNAMIC_LINK",
            "DW_BUILD_DLL",
            -- silence the noise from external libraries
            "_CRT_SECURE_NO_WARNINGS"
        }

        -- copying DLLs and resoruces
        postbuildcommands {
            -- copy dwarfworks.dll into sandbox
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")
        }

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

    -- specify versions of the run-time library to be used on codegen per build configuration
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

    filter { "system:windows", "configurations:Dist" }
        buildoptions "/MT"

-------------------------
--       Sandbox       --
-------------------------

project "Sandbox"
    -- set project general settings
    location "Sandbox"
    kind "ConsoleApp" -- executable
    language "C++"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    -- set project source files
    files {
        SourceDir .. "/**.h", -- if needed, add `.hpp` files as well
        SourceDir .. "/**.cpp"
    }

    -- set project include directories
    includedirs {
        -- External Logging lib - spdlog
        "Dwarfworks/Vendor/spdlog/include",
        -- The Game Engine - Dwarfworks
        "Dwarfworks/Source"
    }

    -- set project link targets
    links {
        "Dwarfworks"
    }

    -- set project target properties
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        -- preprocessor definitions
        defines {
            "DW_PLATFORM_WINDOWS",
            "DW_DYNAMIC_LINK"
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

    -- specify versions of the run-time library to be used on compilation per build configuration
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

    filter { "system:windows", "configurations:Dist" }
        buildoptions "/MT"
