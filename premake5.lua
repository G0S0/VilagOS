workspace "VilagOS"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--I have no idea what happening here.
IncludeDir = {}
IncludeDir["GLFW"] = "VilagOS/vendor/Glfw"
IncludeDir["Glad"] = "VilagOS/vendor/Glad"
IncludeDir["Imgui"] = "VilagOS/vendor/Imgui"
IncludeDir["glm"] = "VilagOS/vendor/glm"

startproject "Game"

--include "VilagOS/vendor/Glad" --includes a premake5 file from Glad.
include "VilagOS/vendor/Imgui"

project "VilagOS"
	location "VilagOS" --project folder
	kind "StaticLib" 
	language "C++"
	cppdialect "C++17"
	staticruntime "On" --exe links its own runtime library.

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")
	
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{ --.h includes
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}",
		"%{prj.name}/vendor"
	}

	links{ --projects. refferences in solution
		"dependencies/GLFW/glfw3.lib",
		"opengl32.lib",
		--"Glad",
		"dependencies/Glad/Glad.lib",
		"Imgui"
	}

	pchheader "vospch.h"
	pchsource "VilagOS/src/vospch.cpp" --Visual studio needs this 2 work

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines{
			"VOS_PLATFORM_WINDOWS",
			--"VOS_BUILD_DLL",
			"GLFW_INCLUDE_NONE", --I need this so that glad and glfw dont both include opengl.
			"IMGUI_IMPL_LOADER_CUSTOM",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD",
			"IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY",
			"_CRT_SECURE_NO_WARNINGS"
		}

		--postbuildcommands{
		--	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
		--}

	filter "configurations:Debug"
		defines "VOS_DEBUG"
		symbols "On"
		--runtime "Debug"
		buildoptions "/MDd"
	
	filter "configurations:Release"
		defines "VOS_RELEASE"
		symbols "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "VOS_DIST"
		symbols "On"
		buildoptions "/MD"
----------------------------------------------------------------------------------------------

project "Game"
	location "Game" --project folder
	kind "ConsoleApp" --console app
	cppdialect "C++17"
	language "C++"
	staticruntime "On"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"VilagOS/vendor/spdlog/include",
		"VilagOS/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Imgui}",
		"VilagOS/vendor"
	}

	links{
		"VilagOS"
	}


	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		defines{
			"VOS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VOS_DEBUG"
		symbols "On"
		buildoptions "/MDd"
	
	filter "configurations:Release"
		defines "VOS_RELEASE"
		symbols "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "VOS_DIST"
		symbols "On"
		buildoptions "/MD"