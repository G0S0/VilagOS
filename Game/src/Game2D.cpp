#include "Game2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "VilagOS/Renderer/Renderer2D.h"
#include "Random.h"

using namespace VilagOS;

Game2D::Game2D(): Layer("Game2D"){
	auto& window = Application::GetApp().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());
	Random::Init();
	m_Texture.reset(new VilagOS::Texture2D("assets/textures/background.png"));
	m_Level.Init();
}

void Game2D::OnAttach() {
}
void Game2D::OnDetach(){
}

void Game2D::OnUpdate(VilagOS::DeltaTime dt) {
	//OnUpdate
	
	
	

	//for (auto& asteroid : m_Level.GetAsteroids()) {
	//	asteroid.position.y -= m_Level.GetSpeed();
	//	asteroid.rotation += asteroid.rotationSpeed;
	//}
	switch (m_GameState)
	{
	case Game2D::GameState::InGame:
		m_Level.OnUpdate(dt);
		break;
	}

	//OnRender
	VilagOS::RenderCommand::Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1));
	VilagOS::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	
	
	//
	//m_Level.OnRender();
	//this->OnEvent(VilagOS::Event & e);
	VilagOS::Renderer2D::EndScene();
}
void Game2D::OnImGuiRender() {
	
	//ImGui::Begin("Materials");
	//ImGui::End();
}
void Game2D::OnEvent(VilagOS::Event& e) {
	//m_CameraController.OnEvent(e);
	EventDispatcher dispatcher = EventDispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(VOS_BIND_EVENT_FN(Game2D::Resize));
}

bool Game2D::Resize(VilagOS::WindowResizeEvent& e) {
	CreateCamera(e.getSizes().first, e.getSizes().second);
	return false;
}

void Game2D::CreateCamera(uint32_t width, uint32_t height) {
	float aspectRatio = float(width) / float(height);
	float camHeight = 8.0f; //Setting up screen units
	float bottom = -camHeight;
	float top = camHeight;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera.reset(new OrthographicCamera(left, right, bottom, top));
}