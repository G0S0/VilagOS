bool OnCollision()
{
    vec4 Verticies[4] = {
        {-0.5f, 0.5f, 0.0f, 1.0f},
        {-0.5f, -0.5f, 0.0f, 1.0f},
        {0.5f, -0.5f, 0.0f, 1.0f},
        {0.5f, 0.5f, 0.0f, 1.0f}};

    vec4 playerTransformedVerticies[4];

    const auto &position = m_Player.GetPosition();
    const auto &size = m_Player.GetSize();

    for (int i = 0; i < 4; i++)
    {
        playerTransformedVerticies[i] = translate(mat4(1.0f), position) * scale(mat4(1.0f), vec3(size.x, size.y, 1.0f)) * Verticies[i];
    }

    for (auto &asteroid : m_Asteroids)
    {

        vec2 asteroidVertecies[4];

        for (int i = 0; i < 4; i++)
        {
            asteroidVertecies[i] = translate(mat4(1.0f), asteroid.position) * rotate(mat4(1.0f), radians(asteroid.rotation), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(asteroid.size.x, asteroid.size.y, 1.0f)) * Verticies[i];
        }

        for (auto vert : playerTransformedVerticies)
        {
            if (Collided(vec2(vert.x, vert.y), asteroidVertecies[0], asteroidVertecies[1], asteroidVertecies[2], asteroidVertecies[3]))
            {
                return true;
            }
        }
    }
    return false;
}