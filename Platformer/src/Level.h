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
	inline float GetTime() { return m_TimeElapsed; }
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
		bool show;
	};

	struct Floor {
		std::shared_ptr<Texture2D> m_GrassTexture;
		glm::vec3 position;
		glm::vec2 size;
	};
	
private:
	void CreateAsteroid(int index);
	void CreateStar(int index);
	void CreatePlanet(int index);
	void LoadLevel();
	bool OnCollision();
	

private:
	bool m_GameOver = false;
	float m_TimeElapsed = 0.0f;
	float m_Incrament = 5.0f;
	int m_Index = 0;
	
	std::shared_ptr<Texture2D> m_BackgroundTexture;
	std::vector<Floor> m_Floors;
	Player m_Player;

	
};