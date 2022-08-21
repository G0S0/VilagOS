#include "Game2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"

Game2D::Game2D(): Layer("Game2D"), m_CameraController(1280.f / 720.f) {

}

void Game2D::OnAttach() {


	VilagOS::BufferLayout layout = { // layout setup
		{"a_Position", VilagOS::DataType::Float3}
	};

	m_VertexArray.reset(new VilagOS::VertexArray());
	float Verticies[3 * 4] = {
		-0.5f, 0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f, 
		0.5f, 0.5f, 0.0f
	};

	std::shared_ptr<VilagOS::VertexBuffer> m_VertexBuffer;
	m_VertexBuffer.reset(new VilagOS::VertexBuffer(Verticies, sizeof(Verticies)));
	m_VertexBuffer->SetLayout(layout);

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	uint32_t Indicies[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<VilagOS::IndexBuffer> m_IndexBuffer;
	m_IndexBuffer.reset(new VilagOS::IndexBuffer(Indicies, sizeof(Indicies)));

	m_VertexArray->AddIndexBuffer(m_IndexBuffer);

	m_Shader.reset(new VilagOS::Shader("assets/shaders/FlatColor.glsl"));
}
void Game2D::OnDetach(){
}

void Game2D::OnUpdate(VilagOS::DeltaTime dt) {
	//OnUpdate
	m_CameraController.OnUpdate(dt);

	//OnRender
	VilagOS::RenderCommand::Clear(glm::vec4(0.1f, 0.1f, 0.1f, 1));
	VilagOS::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 RectangleTransform = glm::translate(glm::mat4(1.0f), m_RectanglePosition);
	glm::mat4 RectangleTransform2 = glm::translate(glm::mat4(1.0f), m_RectanglePosition + glm::vec3(0.5f));

	m_Shader->Bind();
	m_Shader->UploadUniformVec4(blueColor, "u_Color");
	VilagOS::Renderer::SubmitData(m_Shader, m_VertexArray, RectangleTransform);

	//this->OnEvent(VilagOS::Event & e);
	VilagOS::Renderer::EndScene();
}
void Game2D::OnImGuiRender() {
	ImGui::Begin("Materials");
	ImGui::ColorEdit4("Material1", glm::value_ptr(blueColor));
	//ImGui::ColorEdit4("Material2", glm::value_ptr(someColor));
	ImGui::End();
}
void Game2D::OnEvent(VilagOS::Event& e) {
	m_CameraController.OnEvent(e);
}