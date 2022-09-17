#include "Level.h"
#include "Random.h"
#include "VilagOS/Renderer/Renderer2D.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Level::Init() {
	m_Texture.reset(new VilagOS::Texture2D("assets/textures/GreyAsteroid.png"));
	m_TextureQuad.reset(new VilagOS::Texture2D("assets/textures/background.jpg"));
	m_Textures.resize(6);
	m_Textures[0].reset(new VilagOS::Texture2D("assets/textures/planet.png"));
	m_Textures[1].reset(new VilagOS::Texture2D("assets/textures/red.png"));
	m_Textures[2].reset(new VilagOS::Texture2D("assets/textures/earth.png"));
	m_Textures[3].reset(new VilagOS::Texture2D("assets/textures/smth.png"));
	m_Textures[4].reset(new VilagOS::Texture2D("assets/textures/cyborg.png"));
	m_Player.LoadAssets();
}

void Level::OnUpdate(DeltaTime dt) {
	m_Player.OnUpdate(dt);

	m_TimeElapsed += dt.GetMiliseconds();
	m_AsteroidSpeed = m_Incrament * dt.GetMiliseconds();
	
	if (m_Rounds == 0) {
		m_Asteroids.resize(3);
		for (int i = 0; i < 3; i++) {
			CreateAsteroid(i);
		}

		m_Stars.resize(25);
		for (int i = 0; i < 4; i++) {
			CreateStar(i);
			m_Index = 4;
		}
	}

	if (m_Planet.show) {
		m_Planet.position.y -= m_Planet.speed;
	}

	if (m_TimeElapsed > 15.0f * m_Rounds) {
		m_Rounds++;
		m_Incrament += 3.0f;
		
		if (m_Rounds < 6 && m_Rounds > 1) {
			CreatePlanet(m_Rounds - 1);
			VOS_CORE_INFO("{0}", m_Planet.show);
		}

		if (m_Rounds % 2 == 0) {
			m_Asteroids.resize(std::min(8, ((m_Rounds/2) + 3)));
			CreateAsteroid(m_Asteroids.size() - 1);
		}
	}

	for (auto& asteroid : m_Asteroids) {
		if (asteroid.position.y < -8.5f) {
			CreateAsteroid(asteroid.index);
		}
		asteroid.position.y -= asteroid.speed;
		asteroid.rotation += asteroid.rotationSpeed;
	}

	for (auto& star : m_Stars) {
		if (star.position.y < -8.0f) {
			if (m_TimeElapsed > m_StarCounter) {
				CreateStar(m_Index);
				m_Index = ++m_Index % m_Stars.size();
				m_StarCounter = m_TimeElapsed + (0.9 * dt.GetMiliseconds());
			}
		}
		star.position.y -= star.speed;
	}

	if (OnCollision()) {
		m_GameOver = true;
		return;
	}
}

void Level::OnRender() {
	const glm::vec2 playerPositoion = Level::m_Player.GetPosition();

	for (auto& asteroid : m_Asteroids) {
		Renderer2D::DrawRotatedQuad(glm::vec3{asteroid.position}, asteroid.size, (float)asteroid.rotation, m_Texture);
	}

	for (auto& star : m_Stars) {
		Renderer2D::DrawQuad(star.position, glm::vec2(0.06f, 0.06f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if(m_Planet.position.y > -10.0f && m_Planet.show) {
		VilagOS::Renderer2D::DrawQuad(m_Planet.position, { 2.0f, 2.0f }, m_Planet.planetTexture);
		
	}
	else {
		m_Planet.show = false;
	}

	VilagOS::Renderer2D::DrawQuad({7.08f, 8.0f ,-0.2f}, { 4.0f, 32.0f }, m_TextureQuad);
	VilagOS::Renderer2D::DrawQuad({ -7.08f, 8.0f, -0.2f }, { -4.0f, 32.0f }, m_TextureQuad);
	m_Player.OnRender();
}

void Level::CreateAsteroid(int index) {
	Asteroid& asteroid = m_Asteroids[index];
	asteroid.position = glm::vec3(Random::Dist() * 5.0f * Random::myRandom(), 10.f, index * 0.1f - 0.5f);
	asteroid.speed = std::max(Random::Dist() * m_AsteroidSpeed, 0.5f * m_AsteroidSpeed) ;
	asteroid.rotation = Random::Dist()*360 * Random::myRandom();
	asteroid.rotationSpeed = Random::Dist() * 3;
	asteroid.size = glm::vec2(std::max(Random::Dist() * 1.0f, 0.5f));
	asteroid.index = index;
}

void Level::CreateStar(int index) {
	Star& star = m_Stars[index];
	star.position = glm::vec3(Random::Dist() * 5.0f * Random::myRandom(), 20.0f, -0.1f);
	star.speed = std::max(Random::Dist() * m_AsteroidSpeed + 0.09f, 0.5f * m_AsteroidSpeed + 0.09f);
	star.index = index;
}

void Level::CreatePlanet(int index) {
	m_Planet.planetTexture = m_Textures[index];
	m_Planet.position = glm::vec3(Random::Dist() * 5.0f * Random::myRandom(), 10.f, -0.7f);
	m_Planet.speed = 0.3f * m_AsteroidSpeed;
	m_Planet.show = true;
}

void Level::Reset() {
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


bool Collided(glm::vec2 vert, glm::vec2 vertOne, glm::vec2 vertTwo, glm::vec2 vertThree, glm::vec2 vertFour) {
	float DOne = (vertTwo.x - vertOne.x) * (vert.y - vertOne.y) - (vert.x - vertOne.x) * (vertTwo.y - vertOne.y);
	float DTwo = (vertThree.x - vertTwo.x) * (vert.y - vertTwo.y) - (vert.x - vertTwo.x) * (vertThree.y - vertTwo.y);
	float DThree = (vertFour.x - vertThree.x) * (vert.y - vertThree.y) - (vert.x - vertThree.x) * (vertFour.y - vertThree.y);
	float DFour = (vertOne.x - vertFour.x) * (vert.y - vertFour.y) - (vert.x - vertFour.x) * (vertOne.y - vertFour.y);
	if (DOne >= 0 && DTwo >= 0 && DThree >= 0 && DFour >= 0) { return true; }
	else { return false; }
}

bool Level::OnCollision() {
	glm::vec4 Verticies[4] = {
		{-0.5f, 0.5f, 0.0f, 1.0f },
		{-0.5f, -0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f},
		{0.5f, 0.5f, 0.0f, 1.0f}
	};

	glm::vec4 playerTransformedVerticies[4];
	
	const auto& position = m_Player.GetPosition();
	const auto& size = m_Player.GetSize();

	for (int i = 0; i < 4; i++) {
		playerTransformedVerticies[i] = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f)) * Verticies[i];
	}

	for (auto& asteroid : m_Asteroids) {
		
		glm::vec2 asteroidVertecies[4];

		for (int i = 0; i < 4; i++) {
			asteroidVertecies[i] = glm::translate(glm::mat4(1.0f),  asteroid.position) * glm::rotate(glm::mat4(1.0f), glm::radians(asteroid.rotation) ,glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(asteroid.size.x, asteroid.size.y, 1.0f)) * Verticies[i];
		}

		for (auto vert : playerTransformedVerticies) {
			if (Collided(glm::vec2(vert.x, vert.y), asteroidVertecies[0], asteroidVertecies[1], asteroidVertecies[2], asteroidVertecies[3])) {
				return true;
			}
		}
	}
	return false;
}


