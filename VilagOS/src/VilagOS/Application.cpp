#include "vospch.h"
#include "Application.h"
#include "glad/glad.h"
#include "Log.h"
#include "Core.h"
#include "VilagOS/Input.h"
#include "VilagOS/MouseButtonCodes.h"
#include "VilagOS/KeyCodes.h"
#include "glfw3.h"


namespace VilagOS{

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		VOS_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		m_Window->SetEventCallback(VOS_BIND_EVENT_FN(Application::OnEvent)); //In the end calls the OnEvent fn

		m_ImGuiLayer = new ImguiLayer();
		PushOverlay(m_ImGuiLayer);
		//unsigned int id;
		//glGenVertexArrays(1, &id); //the hell is this?
	}
	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT);
			//for (Layer* layer : m_LayerStack)
			//	layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
			//glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));
			
		}
	}

	void Application::OnEvent(Event& e) {
		for (Layer* layer : m_LayerStack) {
			//VOS_CORE_ERROR(layer->GetName());
		}
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(VOS_BIND_EVENT_FN(Application::OnWindowClose));
		//VOS_CORE_TRACE("{0}", e);
		//VOS_CORE_TRACE((*--it)->GetName());
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();){
			//VOS_CORE_TRACE((*--it)->GetName());
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
		layer->OnAttach(); //
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.LayerStack::PushOverlay(overlay);
		overlay->OnAttach();
	}
}