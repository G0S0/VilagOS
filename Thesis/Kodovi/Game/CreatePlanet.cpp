void CreatePlanet(int index)
{
    m_Planet.planetTexture = m_Textures[index];
    m_Planet.position = vec3(Dist() * 5.0f * myRandom(), 10.f, -0.7f);
    m_Planet.speed = 0.3f * m_AsteroidSpeed;
    m_Planet.show = true;
}