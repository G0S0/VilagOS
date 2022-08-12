#pragma once
#include "Core.h"
#include "Window/WindowMaster.h"
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

		inline WindowMaster& GetWindow() { return *m_Window; };
		inline static Application& GetApp() { return *s_Instance; };
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<WindowMaster> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	//To be defined in a client
	Application* CreateApplication();
}

