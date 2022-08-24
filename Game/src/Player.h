#pragma once
#include "VilagOS.h"

using namespace VilagOS;

class Player {
public:
	void OnUpdate(DeltaTime dt);
	void LoadAssets();
	void OnRender();
	inline glm::vec2 GetPosition() { return m_Position; }
	inline glm::vec2 GetSize() { return m_Size; }
private:
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	float m_Speed;
	std::shared_ptr<Texture2D> m_ShipTexture;
};