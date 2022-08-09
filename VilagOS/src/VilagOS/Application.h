#pragma once
#include "Core.h"
#include "WindowMaster.h"

namespace VilagOS {

	class VOS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	private:
		std::unique_ptr<WindowMaster> m_Window;
		bool m_Running = true;
	};

	//To be defined in a client
	Application* CreateApplication();
}

