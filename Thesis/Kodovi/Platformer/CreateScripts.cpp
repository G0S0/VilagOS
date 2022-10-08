void CreateScripts()
{
    m_Scripts.resize(7);

    for (int i = 0; i < m_Scripts.size(); i++)
    {
        m_Scripts[i].size = vec2(1.5f, 1.4f * 1.5f);
        m_Scripts[i].rotation = 0.0f;
        m_Scripts[i].scriptTexture.reset(new Texture2D("assets/textures/script.png"));
        m_Scripts[i].index = i;
    }
    m_Scripts[0].position = vec3(-3.0f, -3.5f, -0.2f);
    m_Scripts[1].position = vec3(55.0f, -3.5f, -0.2f);
    m_Scripts[2].position = vec3(-12.0f, 17.5f, -0.3f);
    m_Scripts[3].position = vec3(23.0f, 12.5f, -0.3f);
    m_Scripts[4].position = vec3(35.0f, 8.5f, -0.3f);
    m_Scripts[5].position = vec3(23.0f, 27.0f, -0.3f);
    m_Scripts[6].position = vec3(53.0f, 32.0f, -0.3f);
}