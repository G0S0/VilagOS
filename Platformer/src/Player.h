#pragma once
#include "VilagOS.h"

using namespace VilagOS;

class Player {
public:
	void OnUpdate(DeltaTime dt);
	void LoadAssets();
	void OnRender();
	inline glm::vec3 GetPosition() { return m_Position; }
	inline glm::vec2 GetSize() { return m_Size; }
	inline bool GetInAir() { return m_InAir; }
	inline void SetInAir(bool inAir) { m_InAir = inAir; }
	inline float* GetSpeed() { return &m_Speed; }
	void OnImGUIRender();
private:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	float m_Speed;
	float m_FallSpeed;
	float m_JumpSpeed;
	bool m_InAir;
	bool m_EnableJump;
	std::shared_ptr<Texture2D> m_ShipTexture;
};