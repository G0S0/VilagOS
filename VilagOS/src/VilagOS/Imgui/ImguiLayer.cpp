#include "vospch.h"
#include "ImguiLayer.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
//#include "OpenGl/imgui_impl_opengl3_loader.h"
#include "imgui.h"
#include "glfw3.h"
#include "VilagOS/Core/Application.h"
#include "VilagOS/Core/Core.h"
#include "glad/glad.h"



namespace VilagOS {
	ImguiLayer::ImguiLayer(): Layer("ImguiLayer") { //constructor need to ofc create a new layer. Although since it will always be drawn last should I make it an overlay?

	}

	ImguiLayer::~ImguiLayer() {

	}

	void ImguiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
        io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        //ImGuiStyle& style = ImGui::GetStyle();
        //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        //    style.WindowRounding = 0.0f;
        //    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        //}

        Application& app = Application::GetApp();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImguiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
	}

	void ImguiLayer::OnImGuiRender() {
        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);
	}

    void ImguiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::GetApp();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_curretn_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_curretn_context);
        }
    }

}