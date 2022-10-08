void Level::CreateObstacles()
{
    m_Obstacles.resize(8);
    m_Obstacles[0].position = vec3(56.5f, -4.0f, 0.0f);
    m_Obstacles[0].destination = vec3(-15.0f, -4.0f, 0.0f);
    m_Obstacles[0].toChange = vec3(1.0f, 0.0f, 0.0f);
    m_Obstacles[0].speed = 10.0f;

    m_Obstacles[1].position = vec3(-1.5f, 7.3f, 0.0f);
    m_Obstacles[1].destination = vec3(-4.0f, 25.0f, 0.0f);
    m_Obstacles[1].toChange = vec3(0.0, 1.0f, 0.0f);
    m_Obstacles[1].speed = 12.0f;

    m_Obstacles[2].position = vec3(35.6f, 26.5f, 0.0f);
    m_Obstacles[2].destination = vec3(55.5f, 26.5f, 0.0f);
    m_Obstacles[2].toChange = vec3(1.0f, 0.0f, 0.0f);
    m_Obstacles[2].speed = 12.0f;

    for (int i = 0; i < m_Obstacles.size(); i++)
    {
        m_Obstacles[i].size = vec2(1.6f, 1.6f);
        if (i % 3 == 0)
        {
            m_Obstacles[i].obstacleTexture.reset(new Texture2D("assets/textures/insta.png"));
        }
        if (i % 3 == 1)
        {
            m_Obstacles[i].obstacleTexture.reset(new Texture2D("assets/textures/whap.png"));
        }
        if (i % 3 == 2)
        {
            m_Obstacles[i].obstacleTexture.reset(new Texture2D("assets/textures/fb.png"));
        }

        m_Obstacles[i].rotation = 0.0f;
        m_Obstacles[i].startPosition = m_Obstacles[i].position;
        m_Obstacles[i].travel = 0.0f;
        m_Obstacles[i].toTravel = distance(m_Obstacles[i].startPosition, m_Obstacles[i].destination);
        m_Obstacles[i].orientation = true;
        if (dot(m_Obstacles[i].startPosition, m_Obstacles[i].toChange) > dot(m_Obstacles[i].destination, m_Obstacles[i].toChange))
        {
            m_Obstacles[i].speed *= -1.0f;
        }
    }
}