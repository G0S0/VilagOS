bool Level::OnPickup()
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

    for (auto &script : m_Scripts)
    {

        vec2 floorVerticies[4];

        for (int i = 0; i < 4; i++)
        {
            floorVerticies[i] = translate(mat4(1.0f), script.position) * rotate(mat4(1.0f), radians(0.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(script.size.x, script.size.y, 1.0f)) * Verticies[i];
        }

        for (int j = 0; j < 4; j++)
        {
            if (Collided(vec2(playerTransformedVerticies[j].x, playerTransformedVerticies[j].y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3]))
            {
                m_Index = script.index;
                return true;
            }
        }
    }

    return false;
}