#pragma once
#include "VilagOS.h"

using namespace VilagOS;

class Player {
public:
	void OnUpdate(DeltaTime dt);
	void LoadAssets();
	void OnRender();
	inline glm::vec2 GetPosition() { return m_Position; }
private:
	glm::vec2 m_Position;
	float m_Speed;
	std::shared_ptr<Texture2D> m_ShipTexture;
};