#include "vospch.h"
#include "Application.h"
#include "Log.h"
#include "Core.h"
#include "VilagOS/Input.h"
#include "VilagOS/MouseButtonCodes.h"
#include "VilagOS/KeyCodes.h"
#include "glfw3.h"
#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"



namespace VilagOS{

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		VOS_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Camera = OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

		m_Window = std::unique_ptr<WindowMaster>(WindowMaster::Create());
		m_Window->SetEventCallback(VOS_BIND_EVENT_FN(Application::OnEvent)); //In the end calls the OnEvent fn

		m_ImGuiLayer = new ImguiLayer();
		PushOverlay(m_ImGuiLayer);

		//VertexArray
		m_VertexArray.reset(new VertexArray());

		//VertexBuffer:
		float verticies[3 * 7]{ //verticies with colors
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 0.3f,
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(new VertexBuffer(verticies, sizeof(verticies))); //instancing a vertex buffer

		BufferLayout layout = { // layout setup
			{"a_Position", DataType::Float3},
			{"a_Color", DataType::Float4}
			//{"a_Normal", DataType::Float3}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		//IndexBuffer:
		uint32_t indicies[6] = { 0, 1, 2}; 
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(new IndexBuffer(indicies, sizeof(indicies) / sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		//Shader:
		//multiple lines string
		//takes a position of out attribute inside of a vertex buffer.	
		std::string vertexSource = R"( 
			#version 330 core

			layout(location = 0) in vec3 a_Position; 	
			layout(location = 1) in vec4 a_Color; 
	
			uniform mat4 u_ViewProjection;			

			out vec3 o_Position;
			out vec4 o_Color;

			void main(){
			o_Position = a_Position;
			o_Color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}
		)";
	
		std::string fragmentSource = R"( 
			#version 330 core
			layout(location = 0) out vec4 color; 	

			in vec3 o_Position;			
			in vec4 o_Color;

			void main(){
			color = vec4(o_Position * 0.5f + 0.5f, 1.0f);
			color = o_Color;			
			}
		)";
		m_Shader.reset(new Shader(vertexSource, fragmentSource)); //unique ptr.
		//////////////////////////////////////

		m_OtherVertexArray.reset(new VertexArray());
		float OtherVerticies[4 * 7] = {
			-1.0f, 1.0f, 0.0f, 0.8f, 1.0f, 0.5f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.6f, 0.9f, 0.9f, 1.0f,
			1.0f, -1.0f, 0.0f, 0.0f, 0.8f, 0.9f, 1.0f,
			1.0f, 1.0f, 0.0f, 0.9f, 0.4f, 0.8f, 1.0f
		};

		std::shared_ptr<VertexBuffer> m_OtherVertexBuffer;
		m_OtherVertexBuffer.reset(new VertexBuffer(OtherVerticies, sizeof(OtherVerticies)));
		m_OtherVertexBuffer->SetLayout(layout);

		m_OtherVertexArray->AddVertexBuffer(m_OtherVertexBuffer);

		uint32_t otherIndicies[6] = {0, 1, 2, 2, 3, 0};
		std::shared_ptr<IndexBuffer> m_OtherIndexBuffer;
		m_OtherIndexBuffer.reset(new IndexBuffer(otherIndicies, sizeof(otherIndicies)));

		m_OtherVertexArray->AddIndexBuffer(m_OtherIndexBuffer);

		std::string OthervertexSource = R"( 
			#version 330 core

			layout(location = 0) in vec3 a_Position; 	
			layout(location = 1) in vec4 a_Color; 	

			uniform mat4 u_ViewProjection;	

			out vec3 o_Position;
			out vec4 o_Color;

			void main(){
			o_Position = a_Position;
			o_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0f);
			}
		)";

		std::string OtherfragmentSource = R"( 
			#version 330 core
			layout(location = 0) out vec4 color; 	

			in vec3 o_Position;			
			in vec4 o_Color;

			void main(){
			color = u_ViewProjection * vec4(o_Position * 0.5f + 0.5f, 1.0f);
			color = o_Color;			
			}
		)";
		m_OtherShader.reset(new Shader( OthervertexSource, OtherfragmentSource));
		
	}

	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		while (m_Running) {
			//glClearColor(0.1f, 0.1f, 0.1f, 1);
			//glClear(GL_COLOR_BUFFER_BIT);

			RenderCommand::Clear(glm::vec4(0.1f, 0.1f, 0.1f, 1));

			//Renderer::BeginScene(camera, lights, enviroment);

			m_Shader->Bind();
			m_Shader->UploadUniformMat4(m_Camera.GetViewProjectionMatrix(), "u_ViewProjection");
			Renderer::SubmitData(m_OtherVertexArray);

			m_OtherShader->Bind();
			m_OtherShader->UploadUniformMat4(m_Camera.GetViewProjectionMatrix(), "u_ViewProjection");
			Renderer::SubmitData(m_VertexArray);

			//Renderer::EndScene();

			//m_OtherShader->Bind();
			//m_OtherVertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_OtherIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			//
			//m_Shader->Bind();
			//m_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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