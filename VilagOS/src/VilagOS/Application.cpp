#include "vospch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace VilagOS{
	Application::Application() {
		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		
	}
	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		VOS_CLIENT_TRACE(e);
		while (true) {
			m_Window->OnUpdate();
		}
	}
}