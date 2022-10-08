void OnUpdate(DeltaTime dt)
{
	if (CheckInput())
	{
		m_Speed = clamp(m_Speed * dt.GetMiliseconds(), m_Speed -= 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
	}
	if (IsKeyPressedStatic(VOS_KEY_A))
	{
		m_Speed = clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.x -= m_Speed * dt.GetMiliseconds();
	}
	if (IsKeyPressedStatic(VOS_KEY_D))
	{
		m_Speed = clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.x += m_Speed * dt.GetMiliseconds();
	}
	if (IsKeyPressedStatic(VOS_KEY_W))
	{
		m_Speed = clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.y += m_Speed * dt.GetMiliseconds();
	}
	if (IsKeyPressedStatic(VOS_KEY_S))
	{
		m_Speed = clamp(m_Speed * dt.GetMiliseconds(), m_Speed += 8.0f * dt.GetMiliseconds(), 600.0f * dt.GetMiliseconds());
		m_Position.y -= m_Speed * dt.GetMiliseconds();
	}

	m_Position.x = clamp(m_Position.x, -4.75f, 4.75f);
	m_Position.y = clamp(m_Position.y, -8.0f, 8.0f);

	DrawRotatedQuad(m_Position, m_Size, 180.f, m_ShipTexture);
}
