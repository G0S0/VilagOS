void Init()
{
	m_Texture.reset(new Texture2D("assets/textures/GreyAsteroid.png"));
	m_TextureQuad.reset(new Texture2D("assets/textures/background.jpg"));
	m_Textures.resize(6);
	m_Textures[0].reset(new Texture2D("assets/textures/planet.png"));
	m_Textures[1].reset(new Texture2D("assets/textures/red.png"));
	m_Textures[2].reset(new Texture2D("assets/textures/earth.png"));
	m_Textures[3].reset(new Texture2D("assets/textures/smth.png"));
	m_Textures[4].reset(new Texture2D("assets/textures/cyborg.png"));
	m_Player.LoadAssets();
}

void OnUpdate(DeltaTime dt)
{
	m_Player.OnUpdate(dt);

	m_TimeElapsed += dt.GetMiliseconds();
	m_AsteroidSpeed = m_Incrament * dt.GetMiliseconds();

	if (m_Rounds == 0)
	{
		m_Asteroids.resize(3);
		for (int i = 0; i < 3; i++)
		{
			CreateAsteroid(i);
		}

		m_Stars.resize(25);
		for (int i = 0; i < 4; i++)
		{
			CreateStar(i);
			m_Index = 4;
		}
	}

	if (m_Planet.show)
	{
		m_Planet.position.y -= m_Planet.speed;
	}

	if (m_TimeElapsed > 15.0f * m_Rounds)
	{
		m_Rounds++;
		m_Incrament += 3.0f;

		if (m_Rounds < 6 && m_Rounds > 1)
		{
			CreatePlanet(m_Rounds - 1);
			VOS_CORE_INFO("{0}", m_Planet.show);
		}

		if (m_Rounds % 2 == 0)
		{
			m_Asteroids.resize(std::min(8, ((m_Rounds / 2) + 3)));
			CreateAsteroid(m_Asteroids.size() - 1);
		}
	}

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

	for (auto &star : m_Stars)
	{
		if (star.position.y < -8.0f)
		{
			if (m_TimeElapsed > m_StarCounter)
			{
				CreateStar(m_Index);
				m_Index = ++m_Index % m_Stars.size();
				m_StarCounter = m_TimeElapsed + (0.9 * dt.GetMiliseconds());
			}
		}
		star.position.y -= star.speed;
	}

	if (OnCollision())
	{
		m_GameOver = true;
		return;
	}
}

void OnRender()
{
	const vec2 playerPositoion = m_Player.GetPosition();

	for (auto &asteroid : m_Asteroids)
	{
		}

	for (auto &star : m_Stars)
	{
		DrawQuad(star.position, vec2(0.06f, 0.06f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_Planet.position.y > -10.0f && m_Planet.show)
	{
		DrawQuad(m_Planet.position, {2.0f, 2.0f}, m_Planet.planetTexture);
	}
	else
	{
		m_Planet.show = false;
	}

	DrawQuad({7.08f, 8.0f, -0.2f}, {4.0f, -32.0f}, m_TextureQuad);
	DrawQuad({-7.08f, 8.0f, -0.2f}, {-4.0f, -32.0f}, m_TextureQuad);
	m_Player.OnRender();
}

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

void CreateStar(int index)
{
	Star &star = m_Stars[index];
	star.position = vec3(Dist() * 5.0f * myRandom(), 20.0f, -0.1f);
	star.speed = std::max(Dist() * m_AsteroidSpeed + 0.09f, 0.5f * m_AsteroidSpeed + 0.09f);
	star.index = index;
}

void CreatePlanet(int index)
{
	m_Planet.planetTexture = m_Textures[index];
	m_Planet.position = vec3(Dist() * 5.0f * myRandom(), 10.f, -0.7f);
	m_Planet.speed = 0.3f * m_AsteroidSpeed;
	m_Planet.show = true;
}

void Reset()
{
	m_Player.LoadAssets();
	m_AsteroidIndex = 0;
	m_TimeElapsed = 0.0f;
	m_Incrament = 17.0f;
	m_Rounds = 0;
	m_Index = 0;
	m_StarCounter = 0;
	m_Planet.show = false;
	m_Planet.position.y = 11.0f;
	m_GameOver = false;
	m_Asteroids.clear();
	m_Stars.clear();
}

bool Collided(vec2 vert, vec2 vertOne, vec2 vertTwo, vec2 vertThree, vec2 vertFour)
{
	float DOne = (vertTwo.x - vertOne.x) * (vert.y - vertOne.y) - (vert.x - vertOne.x) * (vertTwo.y - vertOne.y);
	float DTwo = (vertThree.x - vertTwo.x) * (vert.y - vertTwo.y) - (vert.x - vertTwo.x) * (vertThree.y - vertTwo.y);
	float DThree = (vertFour.x - vertThree.x) * (vert.y - vertThree.y) - (vert.x - vertThree.x) * (vertFour.y - vertThree.y);
	float DFour = (vertOne.x - vertFour.x) * (vert.y - vertFour.y) - (vert.x - vertFour.x) * (vertOne.y - vertFour.y);
	if (DOne >= 0 && DTwo >= 0 && DThree >= 0 && DFour >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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
