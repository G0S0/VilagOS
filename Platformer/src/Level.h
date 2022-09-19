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
	inline float GetScore() { return m_Score; }

	inline bool IsGameOver() { return m_GameOver; }
	inline bool IsVictorious() { return m_Victory; }
private:
	struct Script {
		float rotation;
		glm::vec3 position;
		glm::vec2 size;
		std::shared_ptr<Texture2D> scriptTexture;
		int index;
	};

	struct Floor {
		std::shared_ptr<Texture2D> grassTexture;
		glm::vec3 position;
		glm::vec2 size;
	};

	struct Obstacle {
		std::shared_ptr<Texture2D> obstacleTexture;
		glm::vec3 position;
		glm::vec3 startPosition;
		glm::vec3 toChange;
		glm::vec3 destination;
		glm::vec2 size;
		float rotation;
		float travel;
		float speed;
		float toTravel;
		bool orientation;
	};

	
private:
	void CreateScripts();
	void CreatePlatforms();
	void CreateFloors();
	void CreateObstacles();

	bool OnCollision();
	bool OnPickup();
	bool OnHit();

	void LoadLevel();

private:
	bool m_GameOver = false;
	float m_TimeElapsed = 0.0f;
	float m_Incrament = 5.0f;
	int m_Score = 0;
	std::vector<Script>::iterator m_Itr;
	int m_Index;
	bool m_Flag;
	bool m_Victory;
	float m_CountDown;
	
	
	std::vector<Floor> m_Floors;
	std::vector<Floor> m_FlyingStuff;
	std::vector<Script> m_Scripts;
	std::vector<Obstacle> m_Obstacles;
	Player m_Player;

	
};