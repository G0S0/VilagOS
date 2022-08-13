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
IncludeDir["Glad"] = "VilagOS/vendor/Glad/include"
IncludeDir["Imgui"] = "VilagOS/vendor/Imgui"
IncludeDir["glm"] = "VilagOS/vendor/glm"

startproject "Game"

include "VilagOS/vendor/Glad" --includes a premake5 file from Glad.
include "VilagOS/vendor/Imgui"

project "VilagOS"
	location "VilagOS" --project folder
	kind "SharedLib" --dll files
	language "C++"

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
		"Glad",
		"Imgui"
	}

	pchheader "vospch.h"
	pchsource "VilagOS/src/vospch.cpp" --Visual studio needs this 2 work

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"VOS_PLATFORM_WINDOWS",
			"VOS_BUILD_DLL",
			"GLFW_INCLUDE_NONE", --I need this so that glad and glfw dont both include opengl.
			"IMGUI_IMPL_LOADER_CUSTOM",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD",
			"IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
		}

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
	language "C++"

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
		"%{IncludeDir.Imgui}"
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
		buildoptions "/MDd"
	
	filter "configurations:Release"
		defines "VOS_RELEASE"
		symbols "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "VOS_DIST"
		symbols "On"
		buildoptions "/MD"