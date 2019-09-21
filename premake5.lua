workspace "Dwarfworks"
	architecture "x64"

	configurations {
		"Debug", -- Full on debug code enabled with all information available
		"Release", -- Stripped out a lot of debug info, but some (like Logging) is kept
		"Dist" -- build to be distributed to the public with all debug info stripped
	}

-- platform-independent output directory definition
local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
-- description ...
local sourcedir = "%{prj.name}/Source"

----------------------------
--       Dwarfworks       --
----------------------------

project "Dwarfworks"
	-- set project general settings
	location "Dwarfworks"
	kind "SharedLib" -- dynamically linked library (DLL)
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- set project source files
	files {
		-- Dwarfworks root
		sourcedir .. "/**.h",
		sourcedir .. "/**.cpp",
		-- Core module
		sourcedir .. "/Core/**.h",
		sourcedir .. "/Core/**.cpp",
		--/-- Event System
		sourcedir .. "/Core/EventSystem/**.h",
		sourcedir .. "/Core/EventSystem/**.cpp",
		--/--/-- Defaut Events
		sourcedir .. "/Core/EventSystem/Events/**.h",
		sourcedir .. "/Core/EventSystem/Events/**.cpp",
		-- Graphics module
		sourcedir .. "/Graphics/**.h",
		sourcedir .. "/Graphics/**.cpp",
		-- Math module
		sourcedir .. "/Math/**.h",
		sourcedir .. "/Math/**.cpp"
	}

	-- set project include directories
	includedirs {
		-- External Logging lib - spdlog
		"%{prj.name}/Vendor/spdlog/include"
	}

	-- set project target properties
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		-- preprocessor definitions
		defines {
			"DWARF_PLATFORM_WINDOWS",
			"DWARF_DYNAMIC_LINK",
			"DWARF_BUILD_DLL"
		}

		-- copying DLLs and resoruces
		postbuildcommands {
			-- copy dwarfworks.dll into sandbox
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	print("%{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	
	-- specify build and compilation options per build configuration
	filter "configurations:Debug"
		defines "DWARF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DWARF_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DWARF_DIST"
		optimize "On"
	
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

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- set project source files
	files {
		sourcedir .. "/**.h", -- if needed, add `.hpp` files as well
		sourcedir .. "/**.cpp"
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
		staticruntime "On"
		systemversion "latest"

		-- preprocessor definitions
		defines {
			"DWARF_PLATFORM_WINDOWS",
			"DWARF_DYNAMIC_LINK"
		}
	
	-- specify build and compilation options per build configuration
	filter "configurations:Debug"
		defines "DWARF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DWARF_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DWARF_DIST"
		optimize "On"
	
	-- specify versions of the run-time library to be used on codegen per build configuration
	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MTd"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

	filter { "system:windows", "configurations:Dist" }
		buildoptions "/MT"
