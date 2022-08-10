#include "vospch.h"
#include "Application.h"

#include "Log.h"

namespace VilagOS{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); //In the end calls the OnEvent fn
	}
	Application::~Application() {

	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//VOS_CORE_TRACE("{0}", e);
	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		VOS_CLIENT_TRACE(e);
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}