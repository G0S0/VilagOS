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

    for (auto &floor : m_Floors)
    {

        vec2 floorVerticies[4];

        for (int i = 0; i < 4; i++)
        {
            floorVerticies[i] = translate(mat4(1.0f), floor.position) * rotate(mat4(1.0f), radians(0.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(floor.size.x, floor.size.y, 1.0f)) * Verticies[i];
        }

        for (auto vert : playerTransformedVerticies)
        {
            if (Collided(vec2(vert.x, vert.y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3]))
            {
                return true;
            }
        }
    }
}