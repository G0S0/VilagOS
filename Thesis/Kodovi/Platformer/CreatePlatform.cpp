void Level::CreatePlatforms()
{
    m_FlyingStuff.resize(13);
    for (auto &el : m_FlyingStuff)
    {
        el.grassTexture.reset(new Texture2D("assets/textures/grass.png"));
    }
    m_FlyingStuff[0].position = vec3(3.0f, -1.0f, -0.3f);
    m_FlyingStuff[0].size = vec2(5.1f, 0.9f);

    m_FlyingStuff[1].position = vec3(8.0f, 4.0f, -0.3f);
    m_FlyingStuff[1].size = vec2(5.1f, 0.9f);

    m_FlyingStuff[2].position = vec3(23.0f, 10.0f, -0.3f);
    m_FlyingStuff[2].size = vec2(5.1f, 0.9f);

    m_FlyingStuff[3].position = vec3(-1.5f, 7.3f, -0.3f);
    m_FlyingStuff[3].size = vec2(5.1f, 0.9f);

    m_FlyingStuff[4].position = vec3(-12.0f, 15.0f, -0.3f);
    m_FlyingStuff[4].size = vec2(5.1f, 0.9f);
}