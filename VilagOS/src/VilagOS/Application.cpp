#include "vospch.h"
#include "Application.h"
#include "Glad/glad.h"
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

		//VertexArray
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		//VertexBuffer
		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float verticies[3 * 3]{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); //eh?
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

		//IndexBuffer
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indicies[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

		//multiple lines string
		//takes a position of out attribute inside of a vertex buffer.	
		std::string vertexSource = R"( 
			#version 330 core
			layout(location = 0) in vec3 a_Position; 		
			out vec3 position;
			void main(){
			position = a_Position;
			gl_Position = vec4(a_Position, 1.0f);
			}
		)";
	
		std::string fragmentSource = R"( 
			#version 330 core
			layout(location = 0) out vec4 color; 	
			in vec3 position;			

			void main(){
			color = vec4(position * 0.5f + 0.5f, 1.0f);
			}
		)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource)); //unique ptr.

		//unsigned int id;
		//glGenVertexArrays(1, &id); //the hell is this?
	}
	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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