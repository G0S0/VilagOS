#include "Player.h"
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>


void Player::LoadAssets() {
	m_ShipTexture.reset(new Texture2D("assets/textures/unknown.png"));
	m_Position = glm::vec3(-10.0f, -4.75f, 0.0f);
	m_Speed = 10.f;
	m_JumpSpeed = 80.0f;
	m_InAir = false;
	m_Size = glm::vec2(2.5f, -2.5f);
	m_TimeElapsed = 0;
	m_Hp = 3;
	m_SpeedCap = 1000.0f;
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
	if (CheckInput() && !(m_InAir))
	{
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed -= 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
	}

	if (m_InAir) {
		float temp = m_Speed;
		m_FallSpeed = glm::clamp(m_FallSpeed * dt.GetMiliseconds(), m_FallSpeed += 40.0f * dt.GetMiliseconds(), (m_SpeedCap + 100.0f) * dt.GetMiliseconds());
		if (m_FallSpeed > m_Speed || !(Input::IsKeyPressedStatic(VOS_KEY_W))) {
			m_Position.y -= (m_FallSpeed + 4.0f)*dt.GetMiliseconds();
			m_EnableJump = false;
		}
	}
	else {
		m_EnableJump = true;
		m_FallSpeed = 0.0f;
	}

	if (Input::IsKeyPressedStatic(VOS_KEY_A )) {
		
		if (m_InAir) {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x -= (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x -= m_Speed * dt.GetMiliseconds();
		}
		if(m_Size.x < 0.0f)
			m_Size.x *= -1.0f;
	}
	else if (Input::IsKeyPressedStatic(VOS_KEY_D)) {
		if (m_InAir) {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x += (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x += m_Speed * dt.GetMiliseconds();
		}
		if (m_Size.x > 0.0f)
			m_Size.x *= -1.0f;
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_W) && m_EnableJump) {
		if (m_Speed <= 5.0f) {
			m_Speed = 5.0f;
			m_Position.y += (m_Speed)*dt.GetMiliseconds();
		}
		else {
			m_Position.y += (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		
	}
	else if (Input::IsKeyPressedStatic(VOS_KEY_S)) {
		if (m_InAir) {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.y -= (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.y -= m_Speed * dt.GetMiliseconds();
		}
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_LEFT_SHIFT)) {
		m_SpeedCap = 1400.0f;
	}
	else {
		m_SpeedCap = 1000.0f;
	}
	m_Position.x = glm::clamp(m_Position.x, -15.75f, 57.0f);
	m_Position.y = glm::clamp(m_Position.y, -4.75f, 35.0f);
	//VOS_CLIENT_INFO("({0}, {1})", m_Position.x, m_Position.y);
}

void Player::OnRender() {
	Renderer2D::DrawRotatedQuad(m_Position, m_Size, 180.f, m_ShipTexture);
	//OnImGUIRender();
}

void Player::OnImGUIRender() {
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;
	ImGui::Begin("variables", new bool(true), flags);
	ImGui::SliderFloat("m_speed", GetSpeed(), 10.0f, 1000.0f);
	//ImGui::ColorEdit4("Material2", glm::value_ptr(someColor));
	ImGui::End();
}