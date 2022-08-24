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
	
}

void Game2D::OnAttach() {
	m_Level.Init();
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/VT323-Regular.ttf", 120.0f);
	m_Texture.reset(new VilagOS::Texture2D("assets/textures/background.png"));
	m_GameState = GameState::MainMenu;
}

void Game2D::OnDetach() {

}

void Game2D::OnUpdate(VilagOS::DeltaTime dt) {
	//OnUpdate
	if (m_Level.IsGameOver())
		m_GameState = GameState::GameOver;

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
	OnImGuiRender();
	VilagOS::Renderer2D::EndScene();
}

void Game2D::OnImGuiRender() {
	
	switch (m_GameState)
	{
	case Game2D::GameState::InGame: {
		//std::string toPrint = std::string("Time: ") + std::to_string(m_Level.GetTime());
		//ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 48.0f, toPrint.c_str());
		//break;
	}
	case Game2D::GameState::GameOver: {
		break;
	}
	case Game2D::GameState::MainMenu: {
		break;
	}

	}
	
}
void Game2D::OnEvent(VilagOS::Event& e) {
	EventDispatcher dispatcher = EventDispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(VOS_BIND_EVENT_FN(Game2D::Resize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(VOS_BIND_EVENT_FN(Game2D::OnMousePressed));
}

bool Game2D::Resize(VilagOS::WindowResizeEvent& e) {
	CreateCamera(e.getSizes().first, e.getSizes().second);
	return false;
}

bool Game2D::OnMousePressed(VilagOS::MouseButtonPressedEvent& e) {
	if (m_GameState == GameState::GameOver) {
		m_Level.Reset();
		m_GameState = GameState::InGame;
	}
		

	if (m_GameState == GameState::InGame)
		m_GameState = GameState::MainMenu;
	else if (m_GameState == GameState::MainMenu)
		m_GameState = GameState::InGame;

	//m_GameState = GameState::InGame;

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