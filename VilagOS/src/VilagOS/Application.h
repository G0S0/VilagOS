#pragma once
#include "Core.h"

namespace VilagOS {

	class VOS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};

	//To be defined in a client
	Application* CreateApplication();
}

