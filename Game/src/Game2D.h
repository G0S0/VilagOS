#pragma once
#include "VilagOS.h"

class Game2D: public VilagOS::Layer{
public:
	Game2D();
	~Game2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(VilagOS::DeltaTime dt) override;
	virtual void OnImGuiRender() override;
	void OnEvent(VilagOS::Event& e) override;
private:
	std::shared_ptr<VilagOS::Shader> m_Shader;
	std::shared_ptr<VilagOS::VertexArray> m_VertexArray;

	glm::vec4 blueColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);

	VilagOS::OrthographicCameraController m_CameraController;

	glm::vec3 m_RectanglePosition = glm::vec3(0.0f);
}; 