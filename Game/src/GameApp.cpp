#include <VilagOS.h>
#include "imgui.h"

class ExampleLayer : public VilagOS::Layer {
public:
	ExampleLayer() : Layer("Example") {
		m_Camera = VilagOS::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

		//VertexArray
		m_VertexArray.reset(new VilagOS::VertexArray());

		//VertexBuffer:
		float verticies[3 * 7]{ //verticies with colors
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 0.3f,
		};

		std::shared_ptr<VilagOS::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(new VilagOS::VertexBuffer(verticies, sizeof(verticies))); //instancing a vertex buffer

		VilagOS::BufferLayout layout = { // layout setup
			{"a_Position", VilagOS::DataType::Float3},
			{"a_Color", VilagOS::DataType::Float4}
			//{"a_Normal", DataType::Float3}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		//IndexBuffer:
		uint32_t indicies[6] = { 0, 1, 2 };
		std::shared_ptr<VilagOS::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(new VilagOS::IndexBuffer(indicies, sizeof(indicies) / sizeof(uint32_t)));
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
		m_Shader.reset(new VilagOS::Shader(vertexSource, fragmentSource)); //unique ptr.
		//////////////////////////////////////

		m_OtherVertexArray.reset(new VilagOS::VertexArray());
		float OtherVerticies[4 * 7] = {
			-1.0f, 1.0f, 0.0f, 0.8f, 1.0f, 0.5f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.6f, 0.9f, 0.9f, 1.0f,
			1.0f, -1.0f, 0.0f, 0.0f, 0.8f, 0.9f, 1.0f,
			1.0f, 1.0f, 0.0f, 0.9f, 0.4f, 0.8f, 1.0f
		};

		std::shared_ptr<VilagOS::VertexBuffer> m_OtherVertexBuffer;
		m_OtherVertexBuffer.reset(new VilagOS::VertexBuffer(OtherVerticies, sizeof(OtherVerticies)));
		m_OtherVertexBuffer->SetLayout(layout);

		m_OtherVertexArray->AddVertexBuffer(m_OtherVertexBuffer);

		uint32_t otherIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<VilagOS::IndexBuffer> m_OtherIndexBuffer;
		m_OtherIndexBuffer.reset(new VilagOS::IndexBuffer(otherIndicies, sizeof(otherIndicies)));

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
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}
		)";

		std::string OtherfragmentSource = R"( 
			#version 330 core
			layout(location = 0) out vec4 color; 	

			in vec3 o_Position;			
			in vec4 o_Color;

			void main(){
			color = vec4(o_Position * 0.5f + 0.5f, 1.0f);
			color = o_Color;			
			}
		)";
		m_OtherShader.reset(new VilagOS::Shader(OthervertexSource, OtherfragmentSource));

	}

	void OnUpdate() override {

		if(VilagOS::Input::IsKeyPressedStatic(VOS_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMovementSpeed;
		if (VilagOS::Input::IsKeyPressedStatic(VOS_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMovementSpeed;
		if (VilagOS::Input::IsKeyPressedStatic(VOS_KEY_UP))
			m_CameraPosition.y += m_CameraMovementSpeed;
		if (VilagOS::Input::IsKeyPressedStatic(VOS_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMovementSpeed;
		if (VilagOS::Input::IsKeyPressedStatic(VOS_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed;
		if (VilagOS::Input::IsKeyPressedStatic(VOS_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed;


		VilagOS::RenderCommand::Clear(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		VilagOS::Renderer::BeginScene(m_Camera);
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		VilagOS::Renderer::SubmitData(m_OtherShader, m_OtherVertexArray);
		VilagOS::Renderer::SubmitData(m_Shader, m_VertexArray);
		//this->OnEvent(VilagOS::Event & e);
		//Renderer::EndScene();
	}

	void OnEvent(VilagOS::Event& e) override {
		VilagOS::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<VilagOS::KeyPressedEvent>(VOS_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(VilagOS::KeyPressedEvent& e) {
		return false;
	}

private:
	std::shared_ptr<VilagOS::Shader> m_Shader;
	std::shared_ptr<VilagOS::VertexArray> m_VertexArray;

	std::shared_ptr<VilagOS::Shader> m_OtherShader;
	std::shared_ptr<VilagOS::VertexArray> m_OtherVertexArray;
	
	VilagOS::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_CameraRotation = 0.0f;
	float m_CameraMovementSpeed = 0.1f;
	float m_CameraRotationSpeed = 2.0f;
};

class Game : public VilagOS::Application {
public:
	Game() {
		
		PushLayer(new ExampleLayer());
	}
	~Game() {}
};

VilagOS::Application* VilagOS::CreateApplication() {
	return new Game();
}
