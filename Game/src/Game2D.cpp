#include "Game2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "VilagOS/Renderer/Renderer2D.h"

Game2D::Game2D(): Layer("Game2D"), m_CameraController(1280.f / 720.f) {

}

void Game2D::OnAttach() {
	m_Texture.reset(new VilagOS::Texture2D("assets/textures/checker.png")); //why in on attach instead of constructor?
	m_TextureClan.reset(new VilagOS::Texture2D("assets/textures/clan.png"));
}
void Game2D::OnDetach(){
}

void Game2D::OnUpdate(VilagOS::DeltaTime dt) {
	//OnUpdate
	m_CameraController.OnUpdate(dt);

	//OnRender
	VilagOS::RenderCommand::Clear(glm::vec4(0.1f, 0.1f, 0.1f, 1));
	VilagOS::Renderer2D::BeginScene(m_CameraController.GetCamera());

	VilagOS::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.4f, 1.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
	VilagOS::Renderer2D::DrawQuad({ 1.5f, -1.5f }, { 0.5f, 0.5f }, blueColor);
	VilagOS::Renderer2D::DrawQuad({ -0.5f, -0.5f, -0.1f}, {15.0f, 15.0f}, m_Texture);

	//this->OnEvent(VilagOS::Event & e);
	VilagOS::Renderer2D::EndScene();
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