for (auto &asteroid : m_Asteroids)
{
    if (asteroid.position.y < -8.5f)
    {
        CreateAsteroid(asteroid.index);
    }
    asteroid.position.y -= asteroid.speed;
    asteroid.rotation += asteroid.rotationSpeed;
    DrawRotatedQuad(vec3{asteroid.position}, asteroid.size, (float)asteroid.rotation, m_Texture);
}