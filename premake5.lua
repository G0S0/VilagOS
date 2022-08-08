workspace "VilagOS"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "VilagOS"
	location "VilagOS" --project folder
	kind "SharedLib" --dll files
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	pchheader "vospch.h"
	pchsource "VilagOS/src/vospch.cpp" --Visual studio needs this 2 work

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"VOS_PLATFORM_WINDOWS",
			"VOS_BUILD_DLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

	filter "configurations:Debug"
		defines "VOS_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "VOS_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "VOS_DIST"
		symbols "On"
----------------------------------------------------------------------------------------------

project "Game"
	location "Game" --project folder
	kind "ConsoleApp" --console app
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"VilagOS/vendor/spdlog/include",
		"VilagOS/src"
	}

	links{
		"VilagOS"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"VOS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VOS_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "VOS_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "VOS_DIST"
		symbols "On"