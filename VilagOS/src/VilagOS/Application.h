#pragma once
#include "Core.h"
#include "WindowMaster.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace VilagOS {

	class VOS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
		void OnEvent(Event& e);
		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Layer);
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<WindowMaster> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in a client
	Application* CreateApplication();
}

