project "Imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

    files{
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
        "imgui_tables.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_opengl3.cpp",
        "backends/imgui_impl_opengl3.h"
        --"backends/imgui_impl_opengl3_loader.h"
    }

    includedirs{
        "..",
        "."
    }

    defines{
        "IMGUI_IMPL_LOADER_CUSTOM",
        "IMGUI_IMPL_OPENGL_LOADER_GLAD",
        "IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY"
    }

    filter "system:windows"
        systemversion "latest"
        

    filter {"system:windows", "configurations:Release"}
        defines "VOS_RELEASE"
        symbols "On"
        buildoptions "/MD"

