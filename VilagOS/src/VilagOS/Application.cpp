#include "vospch.h"
#include "Application.h"
#include "Log.h"
#include "Core.h"
#include "VilagOS/Input.h"
#include "VilagOS/MouseButtonCodes.h"
#include "VilagOS/KeyCodes.h"
#include "glfw3.h"
#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"



namespace VilagOS{

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		VOS_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

	

		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		m_Window->SetEventCallback(VOS_BIND_EVENT_FN(Application::OnEvent)); //In the end calls the OnEvent fn

		m_ImGuiLayer = new ImguiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}

	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		while (m_Running) {
			

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
			
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(VOS_BIND_EVENT_FN(Application::OnWindowClose));
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
}