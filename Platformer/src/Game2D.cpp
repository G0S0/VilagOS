#include "Game2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "VilagOS/Renderer/Renderer2D.h"
#include "Random.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.cpp"
#include "backends/imgui_impl_glfw.cpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>


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
	//m_Texture.reset(new VilagOS::Texture2D("assets/textures/background.png"));
	m_BackgroundTexture.reset(new VilagOS::Texture2D("assets/textures/saul.png"));
	m_WallTexture.reset(new VilagOS::Texture2D("assets/textures/wall.png"));
	m_GameState = GameState::MainMenu;
	
}

void Game2D::OnDetach() {

}

void Game2D::OnUpdate(VilagOS::DeltaTime dt) {
	//OnUpdate
	if (m_Level.IsGameOver())
		m_GameState = GameState::GameOver;
	if (m_Level.IsVictorious())
		m_GameState = GameState::Victory;

	switch (m_GameState)
	{
	case Game2D::GameState::InGame:
		m_Level.OnUpdate(dt);
		break;
	}

	if ((Input::IsKeyPressedStatic(VOS_KEY_LEFT_ALT))) {
		m_CameraController->OnUpdate(dt);
		m_CameraController->GetCameraRef()->SetPosition(glm::clamp(m_CameraController->GetCameraRef()->GetPosition(), 
			glm::vec3{ -15.75f /( 8.0f * m_AspectRatio), -2.5f / 8.0f, 0.0f }, glm::vec3{ 57.0f / (8.0f * m_AspectRatio), 20.0f / 8.0f, 0.0f }));
	}
	else {
		m_CameraController->GetCameraRef()->SetPosition({ m_Level.GetPlayer().GetPosition().x / (8.0f * m_AspectRatio), (m_Level.GetPlayer().GetPosition().y + 2.0f) / 8.0f, 0.0f });
	}
	
	//OnRender
	VilagOS::RenderCommand::Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1));
	VilagOS::Renderer2D::BeginScene(m_CameraController->GetCamera());
	VilagOS::Renderer2D::DrawQuad(glm::vec3{ -24.5f, 18.0f, -0.1f }, glm::vec2{ 16.0f, 60.0f }, m_WallTexture, 3.0f);
	VilagOS::Renderer2D::DrawQuad(glm::vec3{ 66.5f, 18.0f, -0.1f }, glm::vec2{ 16.0f, 60.0f }, m_WallTexture, 3.0f);
	VilagOS::Renderer2D::DrawQuad(glm::vec3{0.0f + m_CameraController->GetCameraRef()->GetPosition().x * 8.0f * m_AspectRatio * 0.95, 2.0f + m_CameraController->GetCameraRef()->GetPosition().y * 8.0f * 0.95, -0.9f }, glm::vec2{2.0f * 8.0f * m_AspectRatio + 5.0f, (2.0f * 8.0f) + 5.0f}, m_BackgroundTexture);
	//VOS_CLIENT_INFO("{0}, {1}, {2}", m_CameraController->GetCameraRef()->GetPosition().x, m_Level.GetPlayer().GetPosition().x, m_AspectRatio);
	m_Level.OnRender();
	
	VilagOS::Renderer2D::EndScene();
}

float Round(float var) {
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}

void Game2D::OnImGuiRender() {
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;
	ImGui::Begin("Score", new bool(true), flags);
	auto width = Application::GetApp().GetWindow().GetWidth();
	auto height = Application::GetApp().GetWindow().GetHeight();
	std::stringstream toPrint;
	
	auto pos = ImGui::GetWindowPos();
	pos.x -= 40.0f;
	pos.y -= 20.0f;

	toPrint << "HP: ";
	switch (m_Level.GetPlayer().GetHp())
	{
	case 3:
		toPrint<< "Redovan student" << "\n";
		break;
	case 2:
		toPrint << "Apsolventska" << "\n";
		break;
	case 1:
		toPrint << "Ponavlja godinu" << "\n";
		break;
	case 0:
		toPrint << "Neslavno diplomirao" << "\n";
		break;
	default:
		break;
	}
	toPrint.precision(0);
	toPrint << "Score: " << m_Level.GetScore() << "\n";
	toPrint.precision(2);
	toPrint << "Time: " << std::fixed << m_Level.GetTime()<<"s";
	ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, toPrint.str().c_str());

	switch (m_GameState)
	{
	case Game2D::GameState::GameOver: {
		pos = ImGui::GetWindowPos();
		pos.x += width * 0.5f - 275.0f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, "Click left mouse button to restart.");
		break;
	}
	case Game2D::GameState::MainMenu: {
		pos = ImGui::GetWindowPos();
		pos.x += width * 0.5f - 275.0f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, "Click left mouse button to continue.");
		break;
	}
	case Game2D::GameState::Victory: {
		pos = ImGui::GetWindowPos();
		pos.x += width * 0.5f - 250.0f;
		ImGui::GetForegroundDrawList()->AddText(m_Font, 35.0f, pos, 0Xffffffff, "YOU'VE GRADUATED GOOD JOB!");
		break;
	}
	}
	ImGui::End();
	
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
	if (m_GameState == GameState::GameOver || m_GameState == GameState::Victory) {
		m_Level.Reset();
		m_GameState = GameState::InGame;
	}
		
	if (m_GameState == GameState::InGame)
		m_GameState = GameState::MainMenu;

	else if (m_GameState == GameState::MainMenu)
		m_GameState = GameState::InGame;


	return false;
}

void Game2D::CreateCamera(uint32_t width, uint32_t height) {
	float aspectRatio = float(width) / float(height);
	float camHeight = 8.0f; //Setting up screen units
	float bottom = -camHeight;
	float top = camHeight;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_AspectRatio = aspectRatio;
	m_CameraController.reset(new OrthographicCameraController(left, right, bottom, top, aspectRatio));
}