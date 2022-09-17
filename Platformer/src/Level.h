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

private:
	struct Script {
		float rotation;
		glm::vec3 position;
		glm::vec2 size;
		std::shared_ptr<Texture2D> scriptTexture;
		int index;
	};

	struct Floor {
		std::shared_ptr<Texture2D> m_GrassTexture;
		glm::vec3 position;
		glm::vec2 size;
	};
	
private:
	void CreateScripts();
	void LoadLevel();
	void CreatePlatforms();
	void CreateFloors();
	bool OnCollision();
	bool OnPickup();

private:
	bool m_GameOver = false;
	float m_TimeElapsed = 0.0f;
	float m_Incrament = 5.0f;
	int m_Score = 0;
	std::vector<Script>::iterator m_Itr;
	int m_Index;
	
	std::shared_ptr<Texture2D> m_BackgroundTexture;
	std::vector<Floor> m_Floors;
	std::vector<Floor> m_FlyingStuff;
	std::vector<Script> m_Scripts;
	Player m_Player;

	
};