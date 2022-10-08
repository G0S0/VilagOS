if (m_Planet.position.y > -10.0f && m_Planet.show)
{
    m_Planet.position.y -= m_Planet.speed;
    DrawQuad(m_Planet.position, {2.0f, 2.0f}, m_Planet.planetTexture);
}
else
{
    m_Planet.show = false;
}