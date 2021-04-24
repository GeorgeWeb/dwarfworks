workspace "Dwarfworks"
    architecture "x64"
    startproject "Sandbox"

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
IncludeDir["Glad"] = "Dwarfworks/Vendor/glad/include"
IncludeDir["ImGui"] = "Dwarfworks/Vendor/imgui"
IncludeDir["glm"] = "Dwarfworks/Vendor/glm"
IncludeDir["spdlog"] = "Dwarfworks/Vendor/spdlog/include"
IncludeDir["debugbreak"] = "Dwarfworks/Vendor/debugbreak"
IncludeDir["stb_image"] = "Dwarfworks/Vendor/stb_image"
IncludeDir["directx"] = "Dwarfworks/Vendor/directx"

-- define project external dependencies
group "Dependencies"
    include "Dwarfworks/Vendor/glfw"
    include "Dwarfworks/Vendor/glad"
    include "Dwarfworks/Vendor/imgui"

-- relative path to Dwarfworks source folder
local SourceDir = "%{prj.name}/Source"
local VendorDir = "%{prj.name}/Vendor"

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
        SourceDir .. "/*.h",
        SourceDir .. "/*.cpp",
        SourceDir .. "/Dwarfworks/**.h",
        SourceDir .. "/Dwarfworks/**.cpp",
		VendorDir .. "/stb_image/**.h",
		VendorDir .. "/stb_image/**.cpp",
		VendorDir .. "/glm/**.hpp",
		VendorDir .. "/glm/**.inl"
    }

    -- silence external "noise"
    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    -- set project include directories
    includedirs {
        -- the project source folder
        SourceDir,
        -- Cross-platform break into source-line debugger
        "%{IncludeDir.debugbreak}",
        -- External Logging lib - spdlog
        "%{IncludeDir.spdlog}",
        -- SIMD Mathematics
        "%{IncludeDir.glm}",
        -- (cross-platform) Window lib - GLFW
        "%{IncludeDir.GLFW}",
        -- Modern OpenGL profile loader
        "%{IncludeDir.Glad}",
        -- Immediate mode UI
        "%{IncludeDir.ImGui}",
		-- Image decoding/encoding
        "%{IncludeDir.stb_image}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui"
    }

    -- set project target properties

    filter "system:windows"
        systemversion "latest"

        -- Windows specific
        files {
            VendorDir .. "/directx/**.h",
            SourceDir .. "/Platform/Windows/**.h",
            SourceDir .. "/Platform/Windows/**.cpp",
            SourceDir .. "/Platform/OpenGL/**.h",
            SourceDir .. "/Platform/OpenGL/**.cpp",
            SourceDir .. "/Platform/D3D12/**.h",
            SourceDir .. "/Platform/D3D12/**.cpp",
        }

        --
        includedirs {
            -- DirectX helpers
            "%{IncludeDir.directx}"
        }

        -- 
        links {
            -- OpenGL
            "opengl32.lib",
            -- D3D12
            "d3d12.lib",
            "dxgi.lib",
            "dxguid.lib",
        }

        -- preprocessor definitions
        defines {
            -- "DW_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

        -- Temporary disabled until building the engine as a dll gets re-enabled
        -- copying DLLs and resoruces
        -- postbuildcommands {
            -- copy dwarfworks.dll into sandbox
            -- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")
        -- }

    filter "system:linux"
        systemversion "latest"

        -- Linux specific
        files {
            SourceDir .. "/Platform/OpenGL/**.h",
            SourceDir .. "/Platform/OpenGL/**.cpp",
            SourceDir .. "/Platform/Linux/**.h",
            SourceDir .. "/Platform/Linux/**.cpp",
        }

        -- 
        links { 
            "Xrandr",
            "Xi",
            "GLU",
            "GL",
            "X11",
            "dl",
            "pthread",
        }
        
        -- preprocessor definitions
        defines {
            -- "DW_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    print("%{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Sandbox")

    -- specify build and compilation options per build configuration
    filter "configurations:Debug"
        defines {
            "DW_DEBUG"
        }
        
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
        -- Cross-platform break into source-line debugger
        "%{IncludeDir.debugbreak}",
        -- External Logging lib - spdlog
        "%{IncludeDir.spdlog}",
        -- External Mathematics lib - glm
        "%{IncludeDir.glm}"
    }

    -- set project link targets
    links {
        "Dwarfworks"
    }

    -- set project target properties

    filter "system:windows"
        systemversion "latest"

        links {}

        defines {
            -- "DW_DYNAMIC_LINK"
        }

    filter "system:linux"
        links {
            "GLFW",
            "Glad",
            "ImGui",
            "Xrandr",
            "Xi",
            "GLU",
            "GL",
            "X11",
            "dl",
            "pthread",
        }

        defines {
            -- "DW_DYNAMIC_LINK"
        }

    -- specify build and compilation options per build configuration
    filter "configurations:Debug"
        defines {
            "DW_DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "DW_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DW_DIST"
        runtime "Release"
        optimize "on"
