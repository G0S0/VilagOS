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
	//m_Level.OnRender();
	VilagOS::Renderer2D::EndScene();
}

float Round(float var) {
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}

void Game2D::OnImGuiRender() {
	//glm::vec3 blueColor = glm::vec3(1.0f);
	//ImGui::Begin("Materials");
	//ImGui::ColorEdit4("Material1", glm::value_ptr(blueColor));
	////ImGui::ColorEdit4("Material2", glm::value_ptr(someColor));
	//ImGui::End();
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;
	ImGui::Begin("Score", new bool(true), flags);
	auto width = Application::GetApp().GetWindow().GetWidth();
	auto height = Application::GetApp().GetWindow().GetHeight();
	std::stringstream toPrint;

	//auto pos = ImGui::GetWindowPos();
	//pos.x -= 40.0f;
	//pos.y -= 20.0f;
	//toPrint.precision(2);
	//toPrint << "Time: " << std::fixed << m_Level.GetTime() << "s\n" <<
	//	"Round: " << m_Level.GetRounds();
	//ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, toPrint.str().c_str());
	//
	//switch (m_GameState)
	//{
	//case Game2D::GameState::GameOver: {
	//	pos = ImGui::GetWindowPos();
	//	pos.x += width * 0.5f - 275.0f;
	//	ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, "Click left mouse button to restart.");
	//	break;
	//}
	//case Game2D::GameState::MainMenu: {
	//	pos = ImGui::GetWindowPos();
	//	pos.x += width * 0.5f - 275.0f;
	//	ImGui::GetForegroundDrawList()->AddText(m_Font, 30.0f, pos, 0Xffffffff, "Click left mouse button to continue.");
	//	break;
	//}
	//}
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
	if (m_GameState == GameState::GameOver) {
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
	m_Camera.reset(new OrthographicCamera(left, right, bottom, top));
}