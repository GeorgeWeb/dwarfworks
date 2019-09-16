workspace "dwarfworks"
	architecture "x64"

	configurations {
		"Debug", -- Full on debug code enabled with all information available
		"Release", -- Stripped out a lot of debug info, but some (like Logging) is kept
		"Dist" -- build to be distributed to the public with all debug info stripped
	}

-- platform-independent output directory definition
local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

----------------------------
--       Dwarfworks       --
----------------------------

project "dwarfworks"
	-- set project general settings
	location "dwarfworks"
	kind "SharedLib" -- dynamic library
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- set project source files
	files {
		"%{prj.name}/src/**.h", -- if needed, add `.hpp` files as well
		"%{prj.name}/src/**.cpp"
	}

	-- set project include directories
	includedirs {
		"%{prj.name}/vendor/spdlog/include"
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}

	print("%{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
	
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

project "sandbox"
	-- set project general settings
	location "sandbox"
	kind "ConsoleApp" -- executable
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- set project source files
	files {
		"%{prj.name}/src/**.h", -- if needed, add `.hpp` files as well
		"%{prj.name}/src/**.cpp"
	}

	-- set project include directories
	includedirs {
		"dwarfworks/vendor/spdlog/include",
		"dwarfworks/src"
	}

	-- set project link targets
	links {
		"dwarfworks"
	}

	-- set project target properties
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		-- preprocessor definitions
		defines {
			"DWARF_PLATFORM_WINDOWS"
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
