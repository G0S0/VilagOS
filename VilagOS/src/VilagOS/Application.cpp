#include "vospch.h"
#include "Application.h"
#include "glad/glad.h"
#include "Log.h"

namespace VilagOS{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); //In the end calls the OnEvent fn

		unsigned int id;
		glGenVertexArrays(1, &id);
	}
	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		while (m_Running) {
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		VOS_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
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
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.LayerStack::PushOverlay(overlay);
	}
}