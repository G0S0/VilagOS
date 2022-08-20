#include <VilagOS.h>
#include "imgui.h"
#include "DeltaTime.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VilagOS/Renderer/Shader.h"

class ExampleLayer : public VilagOS::Layer {
public:
	ExampleLayer() : Layer("Example") {
		m_CameraController = VilagOS::OrthographicCameraController(1280.0f/720.0f);
		
		//VertexArray
		m_VertexArray.reset(new VilagOS::VertexArray());

		//VertexBuffer:
		float verticies[3 * 7]{ //verticies with colors
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 0.3f
		};

		std::shared_ptr<VilagOS::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(new VilagOS::VertexBuffer(verticies, sizeof(verticies))); //instancing a vertex buffer

		VilagOS::BufferLayout layout = { // layout setup
			{"a_Position", VilagOS::DataType::Float3},
			{"a_Color", VilagOS::DataType::Float4}
			//{"a_Normal", DataType::Float3}
		};

		VilagOS::BufferLayout TextureLayout = { // layout setup
			{"a_Position", VilagOS::DataType::Float3},
			{"a_Texture", VilagOS::DataType::Float2}
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
			uniform mat4 u_Transform;			
			out vec3 o_Position;
			out vec4 o_Color;
			void main(){
			o_Position = a_Position;
			o_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSource = R"( 
			#version 330 core
			layout(location = 0) out vec4 color; 	
			in vec3 o_Position;			
			in vec4 o_Color;

			uniform vec4 u_Color;

			void main(){
			//color = vec4(o_Position * 0.5f + 0.5f, 1.0f);
			color = u_Color;			
			}
		)";
		m_Shader.reset(new VilagOS::Shader("Shader", vertexSource, fragmentSource)); //unique ptr.
		//////////////////////////////////////

		m_OtherVertexArray.reset(new VilagOS::VertexArray());
		float OtherVerticies[5 * 4] = {
			-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f
		};

		std::shared_ptr<VilagOS::VertexBuffer> m_OtherVertexBuffer;
		m_OtherVertexBuffer.reset(new VilagOS::VertexBuffer(OtherVerticies, sizeof(OtherVerticies)));
		m_OtherVertexBuffer->SetLayout(TextureLayout);

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
			uniform mat4 u_Transform;
			out vec3 o_Position;
			out vec4 o_Color;
			void main(){
			o_Position = a_Position;
			o_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string OtherfragmentSource = R"( 
			#version 330 core
			layout(location = 0) out vec4 color; 	
			in vec3 o_Position;			
			in vec4 o_Color;
		
			uniform vec4 u_Color;
			uniform vec2 u_Texture;

			void main(){
			//color = vec4(o_Position * 0.5f + 0.5f, 1.0f);
			color = o_Color;			
			}
		)";
		m_OtherShader.reset(new VilagOS::Shader("OtherShader", OthervertexSource, OtherfragmentSource));


		auto TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		TextureShader.reset(new VilagOS::Shader("assets/shaders/Texture.glsl"));

		
		m_Texture.reset(new VilagOS::Texture2D("assets/textures/checker.png"));
		m_TextureClan.reset(new VilagOS::Texture2D("assets/textures/clan.png"));
		TextureShader->Bind();
		TextureShader->UploadUniformInt(0, "u_Texture");
	}

	void OnUpdate(float DeltaTime) override {

		m_CameraController.OnUpdate(DeltaTime);

		VilagOS::RenderCommand::Clear(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		VilagOS::Renderer::BeginScene(m_CameraController.GetCamera());
		glm::mat4 TriangleTransform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);
		glm::mat4 TriangleTransformTwo = glm::translate(glm::mat4(1.0f), m_TrianglePosition + glm::vec3(0.5f));
		glm::mat4 TriangleTransformThree = glm::translate(glm::mat4(1.0f), m_TrianglePosition - glm::vec3(1.0f));
		glm::mat4 RectangleTransform = glm::translate(glm::mat4(1.0f), m_RectanglePosition);
		glm::mat4 RectangleTransform2 = glm::translate(glm::mat4(1.0f), m_RectanglePosition + glm::vec3(0.5f));

		//Material
		 
		//m_Texture->Bind();
		//VilagOS::Renderer::SubmitData(m_TextureShader, m_OtherVertexArray, RectangleTransform);

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		VilagOS::Renderer::SubmitData(textureShader, m_OtherVertexArray, RectangleTransform);
		m_TextureClan->Bind();
		VilagOS::Renderer::SubmitData(textureShader, m_OtherVertexArray, RectangleTransform);

		//m_OtherShader->Bind();
		//m_OtherShader->UploadUniformVec4(someColor, "u_Color");
		//VilagOS::Renderer::SubmitData(m_OtherShader, m_OtherVertexArray, RectangleTransform);
		//m_OtherShader->Unbind();
		
		m_Shader->Bind();
		m_Shader->UploadUniformVec4(someColor, "u_Color");
		VilagOS::Renderer::SubmitData(m_Shader, m_VertexArray, TriangleTransformThree);
		//m_Shader->UploadUniformVec4(blueColor, "u_Color");
		//VilagOS::Renderer::SubmitData(m_Shader, m_VertexArray, TriangleTransformTwo);
		//m_Shader->UploadUniformVec4(blueColor, "u_Color");
		//VilagOS::Renderer::SubmitData(m_Shader, m_VertexArray, TriangleTransformThree);

		//for (int i = 0; i < 5; i++) {
		//	glm::mat4 TriangleTransform = glm::translate(glm::mat4(1.0f), m_TrianglePosition + glm::vec3(0.5f * i)) * scale;
		//	if (i % 2 == 0)
		//		m_Shader->UploadUniformVec4(blueColor, "u_Color");
		//	else
		//		m_Shader->UploadUniformVec4(someColor, "u_Color");
		//	VilagOS::Renderer::SubmitData(m_Shader, m_VertexArray, TriangleTransform);
		//}

		//this->OnEvent(VilagOS::Event & e);
		//Renderer::EndScene();
	}

	void OnEvent(VilagOS::Event& e) override {
		m_CameraController.OnEvent(e);
		VilagOS::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<VilagOS::KeyPressedEvent>(VOS_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(VilagOS::KeyPressedEvent& e) {
		return false;
	}

	void OnImGuiRender() override{
		//ImGui::Begin("Materials");
		//ImGui::ColorEdit4("Material1", glm::value_ptr(blueColor));
		//ImGui::ColorEdit4("Material2", glm::value_ptr(someColor));
		//ImGui::End();
	}

private:
	VilagOS::ShaderLibrary m_ShaderLibrary;

	std::shared_ptr<VilagOS::Shader> m_Shader;
	std::shared_ptr<VilagOS::VertexArray> m_VertexArray;

	std::shared_ptr<VilagOS::Shader> m_OtherShader;
	std::shared_ptr<VilagOS::VertexArray> m_OtherVertexArray;

	std::shared_ptr<VilagOS::Texture2D> m_Texture, m_TextureClan;
	
	VilagOS::OrthographicCameraController m_CameraController;

	glm::vec3 m_RectanglePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_TrianglePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_TriangleMovementSpeed = 0.1f;
	
	glm::vec4 blueColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
	glm::vec4 someColor = glm::vec4(0.9f, 0.1f, 0.3f, 1.0f);
	
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
