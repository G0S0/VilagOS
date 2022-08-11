#include "vospch.h"
#include "ImguiLayer.h"
#include "OpenGl/imgui_impl_opengl3.h"
#include "imgui.h"
#include "glfw3.h"
#include "VilagOS/Application.h"
#include "VilagOS/Events/KeyboardEvent.h"
#include "VilagOS/Events/MouseEvent.h"


namespace VilagOS {
	ImguiLayer::ImguiLayer(): Layer("ImguiLayer") { //constructor need to ofc create a new layer. Although since it will always be drawn last should I make it an overlay?

	}

	ImguiLayer::~ImguiLayer() {

	}

	void ImguiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410"); //Initialazing.. what?
	}

	void ImguiLayer::OnDetach() {

	}

	void ImguiLayer::OnUpdate() {

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApp();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //Why is there no namespace here? 
	}

	void ImguiLayer::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN())
	}

	void ImguiLayer::OnKeyPressed() {

	}

	static ImGuiKey getImGuiKey(int key) {
		switch(key)
		{
		case GLFW_KEY_TAB: return ImGuiKey_Tab;
		case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
		case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
		case GLFW_KEY_UP: return ImGuiKey_UpArrow;
		case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
		case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
		case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
		case GLFW_KEY_HOME: return ImGuiKey_Home;
		case GLFW_KEY_END: return ImGuiKey_End;
		case GLFW_KEY_INSERT: return ImGuiKey_Insert;
		case GLFW_KEY_DELETE: return ImGuiKey_Delete;
		case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
		case GLFW_KEY_SPACE: return ImGuiKey_Space;
		case GLFW_KEY_ENTER: return ImGuiKey_Enter;
		case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
		default: return ImGuiKey_None;
		}
		
	}


}