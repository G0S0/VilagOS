#include "Player.h"
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>


void Player::LoadAssets() {
	m_ShipTexture.reset(new Texture2D("assets/textures/unknown.png"));
	m_Position = glm::vec3(0.0f, -6.0f, 0.0f);
	m_Speed = 10.f;
	m_JumpSpeed = 80.0f;
	m_FallSpeed = 0.0f;
	m_InAir = false;
	m_Size = glm::vec2(2.5f, 2.5f);
	m_TimeElapsed = 0;
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
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed -= 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
	}

	if (m_InAir) {
		float temp = m_Speed;
		m_FallSpeed = glm::clamp(m_FallSpeed * dt.GetMiliseconds(), m_FallSpeed += 25.0f * dt.GetMiliseconds(), 700.0f * dt.GetMiliseconds());
		if (m_FallSpeed > m_Speed || !(Input::IsKeyPressedStatic(VOS_KEY_W))) {
			m_Position.y -= (m_FallSpeed + 4.0f)*dt.GetMiliseconds();
			m_EnableJump = false;
		}
		VOS_CLIENT_INFO("m_speed: {0}; fall_speed: {1};", m_Speed, m_FallSpeed);
	}
	else {
		m_EnableJump = true;
		m_FallSpeed = 0.0f;
	}

	if (Input::IsKeyPressedStatic(VOS_KEY_A )) {
		
		if (m_InAir) {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
			m_Position.x -= (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
			m_Position.x -= m_Speed * dt.GetMiliseconds();
		}

	}
	else if (Input::IsKeyPressedStatic(VOS_KEY_D)) {
		if (m_InAir) {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
			m_Position.x += (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else {
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
			m_Position.x += m_Speed * dt.GetMiliseconds();
		}
	}
	if (Input::IsKeyPressedStatic(VOS_KEY_W) && m_EnableJump) {
		//m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		if (m_Speed <= 5.0f) {
			m_Speed = 5.0f;
			m_Position.y += (m_Speed)*dt.GetMiliseconds();
		}
		else {
			m_Position.y += (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		
	}
	//else if (Input::IsKeyPressedStatic(VOS_KEY_S)) {
	//	m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
	//	m_Position.y -= m_Speed * dt.GetMiliseconds();
	//}
	m_Position.x = glm::clamp(m_Position.x, -10.75f, 100.0f);
	m_Position.y = glm::clamp(m_Position.y, -5.0f, 8.0f);
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