#pragma once
#include "VilagOS.h"
#include "Level.h"

class Game2D: public VilagOS::Layer{
public:
	Game2D();
	~Game2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(VilagOS::DeltaTime dt) override;
	virtual void OnImGuiRender() override;
	void OnEvent(VilagOS::Event& e) override;
	void CreateCamera(uint32_t width, uint32_t height);
	bool Resize(VilagOS::WindowResizeEvent& e);
	bool OnMousePressed(VilagOS::MouseButtonPressedEvent& e);
private:
	std::shared_ptr<VilagOS::Shader> m_Shader;
	std::shared_ptr<VilagOS::VertexArray> m_VertexArray;
	std::shared_ptr<VilagOS::Texture2D> m_Texture; 
	std::shared_ptr<VilagOS::Texture2D> m_TextureClan;  

	std::unique_ptr<VilagOS::OrthographicCamera> m_Camera;
	
	enum class GameState {
		InGame = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_GameState;
	
	Level m_Level;

	ImFont* m_Font;

	glm::vec3 m_RectanglePosition = glm::vec3(0.0f);
}; 