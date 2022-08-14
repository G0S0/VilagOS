#pragma once
#include "Core.h"
#include "Window/WindowMaster.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "VilagOS/Imgui/ImguiLayer.h"
#include "VilagOS/Renderer/Shader.h"

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
		static Application* s_Instance;
		bool m_Running = true;

		std::unique_ptr<WindowMaster> m_Window;

		ImguiLayer* m_ImGuiLayer;
		
		LayerStack m_LayerStack;
		
		unsigned int m_VertexBuffer, m_VertexArray, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	//To be defined in a client
	Application* CreateApplication();
}

