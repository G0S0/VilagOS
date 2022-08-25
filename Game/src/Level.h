#pragma once
#include "VilagOS.h"
#include "Player.h"

using namespace VilagOS;

class Level {
public:
	void Init();
	void OnRender();
	void OnUpdate(DeltaTime dt);
	void OnImguiRender();
	void Reset();

	inline Player& GetPlayer() { return m_Player; }
	inline float GetSpeed() { return m_AsteroidSpeed; }
	inline float GetTime() { return m_TimeElapsed; }
	inline int GetRounds() { return m_Rounds; }
	inline bool IsGameOver() { return m_GameOver; }

private:
	struct Asteroid {
		float speed;
		glm::vec3 position;
		glm::vec2 size;
		float rotation;
		float rotationSpeed;
		int index;
	};

	struct Star {
		float speed;
		glm::vec3 position;
		int index;
	};

	struct Planet {
		std::shared_ptr<Texture2D> planetTexture;
		glm::vec3 position;
		float speed;
	};
	
private:
	void CreateAsteroid(int index);
	void CreateStar(int index);
	bool OnCollision();
	inline void SetSpeed(float speed) { m_AsteroidSpeed = speed; }
	

private:
	bool m_GameOver = false;
	float m_AsteroidSpeed;
	int m_AsteroidIndex = 0;
	float m_TimeElapsed = 0.0f;
	float m_Incrament = 5.0f;
	int m_Rounds = 0;
	int m_Index = 0;
	int m_StarCounter = 0;
	uint32_t m_AsteroidRateCoeficient = 3;
	std::vector<Asteroid> m_Asteroids;
	std::vector<Star> m_Stars;
	std::vector<Planet> m_Planets;
	std::shared_ptr<Texture2D> m_Texture;
	std::shared_ptr<Texture2D> m_TextureQuad;
	Player m_Player;

	
};