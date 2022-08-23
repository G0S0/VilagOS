#include "Level.h"
#include "Random.h"
#include "VilagOS/Renderer/Renderer2D.h"

void Level::Init() {
	m_Texture.reset(new VilagOS::Texture2D("assets/textures/GreyAsteroid.png"));
	m_TextureQuad.reset(new VilagOS::Texture2D("assets/textures/background.jpg"));
	//m_Player.LoadAssets();

	

}

void Level::OnUpdate(DeltaTime dt) {
	//m_Player.OnUpdate(dt);

	//if (OnCollision()) {
	//	GameOver();
	//	return;
	//}

	m_TimeElapsed += dt.GetMiliseconds();
	m_AsteroidSpeed = m_Incrament * dt.GetMiliseconds();
	
	if (m_Rounds == 0) {
		m_Asteroids.resize(3);
		for (int i = 0; i < 3; i++) {
			CreateAsteroid(i);
		}

		m_Stars.resize(15);
		for (int i = 0; i < 4; i++) {
			CreateStar(i);
			m_Index = 4;
		}
		
	}

	if (m_TimeElapsed > 17.0f * m_Rounds) {
		m_Rounds++;
		m_Incrament += 0.5;
		
		if (m_Rounds % 2 == 0) {
			m_Asteroids.resize(std::min(6, ((m_Rounds/2) + 3)));
			CreateAsteroid(m_Asteroids.size() - 1);
		}
			
	}

	for (auto& asteroid : m_Asteroids) {
		if (asteroid.position.y < -9.0f) {
			CreateAsteroid(asteroid.index);
			
		}
	}

	for (auto& star : m_Stars) {
		if (star.position.y < -8.0f) {
			CreateStar(m_Index);
			m_Index = ++m_Index % m_Stars.size();
		}
	}
}

void Level::OnRender() {
	const glm::vec2 playerPositoion = Level::m_Player.GetPosition();

	//if (m_TimeElapsed > 30 * m_Rounds) {
	//	auto it = 
	//	VilagOS::Renderer2D::DrawQuad({ 7.08f, 8.0f }, { 4.0f, 32.0f }, );
	//}


	for (auto& asteroid : m_Asteroids) {
		asteroid.position.y -= asteroid.speed;
		asteroid.rotation += asteroid.rotationSpeed;
		Renderer2D::DrawRotatedQuad(asteroid.position, glm::vec2(asteroid.size), (float)asteroid.rotation, m_Texture);
	}

	for (auto& star : m_Stars) {
		star.position.y -= star.speed;
		Renderer2D::DrawQuad(star.position, glm::vec2(0.06f, 0.06f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	VilagOS::Renderer2D::DrawQuad({7.08f, 8.0f }, { 4.0f, 32.0f }, m_TextureQuad);
	VilagOS::Renderer2D::DrawQuad({ -7.08f, 8.0f }, { -4.0f, 32.0f }, m_TextureQuad);


}

void Level::CreateAsteroid(int index) {
	Asteroid& asteroid = m_Asteroids[index];
	asteroid.position = glm::vec2(Random::Dist() * 5.0f * Random::myRandom(), 10.f);
	asteroid.speed = std::max(Random::Dist() * m_AsteroidSpeed, 0.5f * m_AsteroidSpeed) ;
	asteroid.rotation = Random::Dist()*360 * Random::myRandom();
	asteroid.rotationSpeed = Random::Dist() * 3;
	asteroid.size = std::max(Random::Dist() * 1.0f, 0.5f);
	asteroid.index = index;
}

void Level::CreateStar(int index) {
	Star& star = m_Stars[index];
	star.position = glm::vec3(Random::Dist() * 5.0f * Random::myRandom(), 20.0f, -0.1f);
	star.speed = std::max(Random::Dist() * m_AsteroidSpeed + 0.09f, 0.5f * m_AsteroidSpeed + 0.09f);
	star.index = index;
}

void Level::GameOver() {
	
}


