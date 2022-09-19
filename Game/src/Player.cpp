#include "Player.h"

void Player::LoadAssets() {
	m_ShipTexture.reset(new Texture2D("assets/textures/ship.png"));
	m_Position = glm::vec3(0.0f, -6.0f, 0.0f);
	m_Speed = 10.f;
	m_Size = glm::vec2(0.75f, 0.75f);
}

bool CheckInput() {
	if (!(Input::IsKeyPressedStatic(VOS_KEY_A) || Input::IsKeyPressedStatic(VOS_KEY_W) ||
		Input::IsKeyPressedStatic(VOS_KEY_D) || Input::IsKeyPressedStatic(VOS_KEY_S))) {
		return true;
	}
	else
		return false;
}

void Player::OnUpdate(DeltaTime dt) {
	if (CheckInput())
	{
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed -= 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_A )) {
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds()) ;
		m_Position.x -= m_Speed * dt.GetMiliseconds();
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_D)) {
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.x += m_Speed * dt.GetMiliseconds();
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_W)) {
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.y += m_Speed * dt.GetMiliseconds();
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_S)) {
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.y -= m_Speed * dt.GetMiliseconds();
	}
	
	m_Position.x = glm::clamp(m_Position.x, -4.75f, 4.75f);
	m_Position.y = glm::clamp(m_Position.y, -8.0f, 8.0f);
}

void Player::OnRender() {
	Renderer2D::DrawRotatedQuad(m_Position, m_Size, 180.f, m_ShipTexture);
}