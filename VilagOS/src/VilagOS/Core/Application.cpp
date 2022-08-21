#include "vospch.h"
#include "Application.h"
#include "Log.h"
#include "Core.h"
#include "VilagOS/Core/Input.h"
#include "VilagOS/Core/MouseButtonCodes.h"
#include "VilagOS/Core/KeyCodes.h"
#include "glfw3.h"
#include "VilagOS/Renderer/Buffer.h"
#include "VilagOS/Renderer/Renderer.h"
#include <chrono>



namespace VilagOS{

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		VOS_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		m_Window->SetEventCallback(VOS_BIND_EVENT_FN(Application::OnEvent)); //In the end calls the OnEvent fn
		//m_Window->SetVSync(false); //for testing deltatime - it works

		Renderer::Init();

		m_ImGuiLayer = new ImguiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		int i = 0;
		float DeltaTime = 0.0f;
		while (m_Running) {
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			if (!m_Minimized) { //I should do some testing to see if chrono should actually be outside this block - this has beem resolvec: It has to be outside since if got more stuff outsied now
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(DeltaTime);
			}
			m_ImGuiLayer->Begin(); // Why does this not delete imgui window when it is not called?
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate(); //I have to be pulling event from window even when it is minimized so that you know... i can expand it again? 
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(VOS_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(VOS_BIND_EVENT_FN(Application::OnWindowResize));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();){
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.LayerStack::PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.LayerStack::PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.getSizes().first == 0 || e.getSizes().second == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		Renderer::OnWindowResize(e.getSizes().first, e.getSizes().second);
		return false;
	}
}