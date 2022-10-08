void CreateAsteroid(int index)
{
    Asteroid &asteroid = m_Asteroids[index];
    asteroid.position = vec3(Dist() * 5.0f * myRandom(), 10.f, index * 0.1f - 0.5f);
    asteroid.speed = std::max(Dist() * m_AsteroidSpeed, 0.5f * m_AsteroidSpeed);
    asteroid.rotation = Dist() * 360 * myRandom();
    asteroid.rotationSpeed = Dist() * 3;
    asteroid.size = vec2(std::max(Dist() * 1.0f, 0.5f));
    asteroid.index = index;
}