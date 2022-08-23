#pragma once
#include "VilagOS.h"
#include "DeltaTime.h"

class Player {
public:
	//void OnUpdate(DeltaTime dt);
	void LoadAssets();
	inline glm::vec2 GetPosition() { return m_Position; }
private:
	glm::vec2 m_Position;
};