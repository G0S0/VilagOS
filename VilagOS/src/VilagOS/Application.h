#pragma once
#include "Core.h"
#include "WindowMaster.h"
#include "Events/ApplicationEvent.h"

namespace VilagOS {

	class VOS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<WindowMaster> m_Window;
		bool m_Running = true;
	};

	//To be defined in a client
	Application* CreateApplication();
}

