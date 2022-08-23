#include "Level.h"
#include "Random.h"
#include "VilagOS/Renderer/Renderer2D.h"

void Level::Init() {
	m_Texture.reset(new VilagOS::Texture2D("assets/textures/background.png"));
	//m_Player.LoadAssets();
	m_AsteroidSpeed = 2.0f;

	m_Asteroids.resize(3);
	for (int i = 0; i < 3; i++) {
		CreateAsteroid(i, 2.0f);
	}
}

void Level::OnUpdate(DeltaTime dt) {
	//m_Player.OnUpdate(dt);

	//if (OnCollision()) {
	//	GameOver();
	//	return;
	//}

	for (auto& asteroid : m_Asteroids) {
		asteroid.position.y -= m_AsteroidSpeed;
		asteroid.rotation += asteroid.rotationSpeed;
		Renderer2D::DrawRotatedQuad(asteroid.position, glm::vec2(asteroid.size), (float)asteroid.rotation, m_Texture);
	}

	for (auto& asteroid : m_Asteroids) {
		if (asteroid.position.y < -14.0f) {
			CreateAsteroid(m_AsteroidIndex, m_AsteroidSpeed);
			m_AsteroidIndex = ++m_AsteroidIndex % m_Asteroids.size();
		}
	}


}

void Level::OnRender() {
	const glm::vec2 playerPositoion = Level::m_Player.GetPosition();

	//

}

void Level::CreateAsteroid(int index, float speed) {
	Asteroid& asteroid = m_Asteroids[index];
	asteroid.position = glm::vec2(Random::Dist() * 0.4, 3.0f);
	asteroid.speed = Random::Dist() * speed;
	asteroid.rotation = Random::Dist()*360;
	asteroid.rotationSpeed = Random::Dist() * 3;
	asteroid.size = Random::Dist() * 1.5f;
}

void Level::GameOver() {
	
}
