#pragma once
#include "VilagOS.h"
#include "Player.h"

using namespace VilagOS;

class Level {
public:

	void Init();
	void OnRender();
	void OnUpdate(DeltaTime dt);

	inline float GetSpeed() { return m_AsteroidSpeed; }

	struct Asteroid {
		float speed;
		glm::vec2 position;
		float rotation;
		float rotationSpeed;
		float size;
	};

	inline std::vector<Asteroid> GetAsteroids() { return m_Asteroids; }
	inline void SetSpeed(float speed) { m_AsteroidSpeed = speed; }

	inline bool IsGameOver() { return m_GameOver; };

	inline Player& GetPlayer() { return m_Player; }

private:
	void CreateAsteroid(int index, float pos);
	//bool OnCollision();

	void GameOver();
private:
	bool m_GameOver = false;
	float m_AsteroidSpeed;
	int m_AsteroidIndex = 0;
	//std::unordered_map< m_Stars;
	std::vector<Asteroid> m_Asteroids;
	std::shared_ptr<Texture2D> m_Texture;
	Player m_Player;
};