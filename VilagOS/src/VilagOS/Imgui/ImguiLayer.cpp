#include "vospch.h"
#include "ImguiLayer.h"
#include "OpenGl/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"
#include "glfw3.h"
#include "VilagOS/Application.h"
#include "VilagOS/Core.h"
#include "glad/glad.h"



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
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  
	}

	void ImguiLayer::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnKeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnKeyTyped));
		dispatcher.Dispatch<MouseButtonPressedEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnMouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(VOS_BIND_EVENT_FN(ImguiLayer::OnWindowResized));
	}

	bool ImguiLayer::OnKeyPressed(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int key = e.GetKeyCode();
		io.KeysDown[key] = true;
		return false;
	}
	
	bool ImguiLayer::OnKeyReleased(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int key = e.GetKeyCode();
		io.KeysDown[key] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImguiLayer::OnKeyTyped(KeyTypedEvent& e) { //tf is this?
		ImGuiIO& io = ImGui::GetIO();
		int c = e.GetKeyCode();
		if (c > 0 && c < 0x10000) {
			io.AddInputCharacter((unsigned short)c);
		}

		return false;
	}

	bool ImguiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int key = e.getButton();
		io.MouseDown[key] = true;
		VOS_CORE_ERROR(key);
		return false;
	}
	bool ImguiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int key = e.getButton();
		io.MouseDown[key] = false;
		VOS_CORE_ERROR(key);
		return false;
	}
	bool ImguiLayer::OnMouseScrolled(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetX();
		io.MouseWheel += e.GetY();
		return false;
	}
	bool ImguiLayer::OnMouseMoved(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}
	bool ImguiLayer::OnWindowResized(WindowResizeEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getSizes().first, e.getSizes().second);
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); //what the hell is this?
		glViewport(0, 0, e.getSizes().first, e.getSizes().second); //needs glad
		return false;
	}

}