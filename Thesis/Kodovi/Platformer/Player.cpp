void Player::OnUpdate(DeltaTime dt)
{
	if (CheckInput() && !(m_InAir))
	{
		m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed -= 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
	}

	if (m_InAir)
	{
		float temp = m_Speed;
		m_FallSpeed = glm::clamp(m_FallSpeed * dt.GetMiliseconds(), m_FallSpeed += 40.0f * dt.GetMiliseconds(), (m_SpeedCap + 100.0f) * dt.GetMiliseconds());
		if (m_FallSpeed > m_Speed || !(IsKeyPressedStatic(VOS_KEY_W)))
		{
			m_Position.y -= (m_FallSpeed + 4.0f) * dt.GetMiliseconds();
			m_EnableJump = false;
		}
	}
	else
	{
		m_EnableJump = true;
		m_FallSpeed = 0.0f;
	}

	if (IsKeyPressedStatic(VOS_KEY_A))
	{

		if (m_InAir)
		{
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x -= (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else
		{
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x -= m_Speed * dt.GetMiliseconds();
		}
		if (m_Size.x < 0.0f)
			m_Size.x *= -1.0f;
	}
	else if (IsKeyPressedStatic(VOS_KEY_D))
	{
		if (m_InAir)
		{
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x += (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else
		{
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.x += m_Speed * dt.GetMiliseconds();
		}
		if (m_Size.x > 0.0f)
			m_Size.x *= -1.0f;
	}
	if (IsKeyPressedStatic(VOS_KEY_W) && m_EnableJump)
	{
		if (m_Speed <= 5.0f)
		{
			m_Speed = 5.0f;
			m_Position.y += (m_Speed)*dt.GetMiliseconds();
		}
		else
		{
			m_Position.y += (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
	}
	else if (IsKeyPressedStatic(VOS_KEY_S))
	{
		if (m_InAir)
		{
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.y -= (m_Speed + 4.0f) * dt.GetMiliseconds();
		}
		else
		{
			m_Speed = glm::clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), m_SpeedCap * dt.GetMiliseconds());
			m_Position.y -= m_Speed * dt.GetMiliseconds();
		}
	}
	if (IsKeyPressedStatic(VOS_KEY_LEFT_SHIFT))
	{
		m_SpeedCap = 1400.0f;
	}
	else
	{
		m_SpeedCap = 1000.0f;
	}
	m_Position.x = glm::clamp(m_Position.x, -15.75f, 57.0f);
	m_Position.y = glm::clamp(m_Position.y, -4.75f, 35.0f);
	Renderer2D::DrawRotatedQuad(m_Position, m_Size, 180.f, m_ShipTexture);
}
