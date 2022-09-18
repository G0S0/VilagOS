#include "Level.h"
#include "Random.h"
#include "VilagOS/Renderer/Renderer2D.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

void Level::Init() {
	m_Player.LoadAssets();
	LoadLevel();
}

void Level::OnUpdate(DeltaTime dt) {
	m_Player.OnUpdate(dt);

	m_TimeElapsed += dt.GetMiliseconds();
	//VOS_CLIENT_INFO("{0}", m_TimeElapsed);

	for (auto& el : m_Scripts) {
		el.rotation += 1.0f;
	}

	if (OnPickup()) {
		m_Score++;
		for (auto it = m_Scripts.begin(); it != m_Scripts.end(); it++) {
			if (it->index == m_Index) {
				m_Scripts.erase(it);
				break;
			}
		}
	}
	if (m_Flag) {
		if (OnHit()) {
			m_CountDown = m_TimeElapsed;
			m_Flag = false;
			m_Player.GetHit();
			VOS_CLIENT_INFO("HIT!");
		}
	}
	else {
		if (m_TimeElapsed - m_CountDown > 3) {
			m_Flag = true;
		}
	}
	

	if (OnCollision()) {
		m_Player.SetInAir(false);
	}
	else {
		m_Player.SetInAir(true);
	}
}

void Level::OnRender() {
	for (auto& el : m_Floors) {
		VilagOS::Renderer2D::DrawQuad(el.position, el.size, el.grassTexture);
	}
	for (auto& el : m_FlyingStuff) {
		VilagOS::Renderer2D::DrawQuad(el.position, el.size, el.grassTexture);
	}
	for (auto& el : m_Scripts) {
		VilagOS::Renderer2D::DrawRotatedQuadZ(el.position, el.size, (float)el.rotation, el.scriptTexture);
	}
	for (auto& el : m_Obstacles) {
		VilagOS::Renderer2D::DrawRotatedQuad(el.position, el.size, (float)el.rotation, el.obstacleTexture);
	}
	
	m_Player.OnRender();
}

void Level::Reset() {
	m_Player.LoadAssets();
	LoadLevel();
	m_TimeElapsed = 0.0f;
	m_Incrament = 17.0f;
	m_GameOver = false;
}

void Level::CreateFloors() {
	m_Floors.resize(15);
	for (int i = 0; i < m_Floors.size(); i++) {
		m_Floors[i].grassTexture.reset(new VilagOS::Texture2D("assets/textures/grass.png"));
		m_Floors[i].position = glm::vec3(-14.1f + 5 * i, -8.0f, -0.1f);
		m_Floors[i].size = glm::vec2(5.1f, 5.5f);
	}
}

void Level::CreatePlatforms() {
	m_FlyingStuff.resize(2);
	m_FlyingStuff[0].grassTexture.reset(new VilagOS::Texture2D("assets/textures/grass.png"));
	m_FlyingStuff[0].position = glm::vec3(3.0f, -1.0f, -0.3f);
	m_FlyingStuff[0].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[1].grassTexture.reset(new VilagOS::Texture2D("assets/textures/grass.png"));
	m_FlyingStuff[1].position = glm::vec3(8.0f, 4.0f, -0.3f);
	m_FlyingStuff[1].size = glm::vec2(5.1f, 0.9f);
}

void Level::CreateScripts() {
	m_Scripts.resize(2);
	for (int i = 0; i < m_Scripts.size(); i++) {
		m_Scripts[i].size = glm::vec2(1.5f, 1.4f*1.5f);
		m_Scripts[i].rotation = 0.0f;
		m_Scripts[i].scriptTexture.reset(new VilagOS::Texture2D("assets/textures/script.png"));
		m_Scripts[i].index = i;
	}
	m_Scripts[0].position = glm::vec3(8.5f, 4.1f, -0.2f);
	m_Scripts[1].position = glm::vec3(-3.0f, 0.1f, -0.2f);
}

void Level::CreateObstacles() {
	m_Obstacles.resize(2);
	for (int i = 0; i < m_Obstacles.size(); i++) {
		m_Obstacles[i].size = glm::vec2(1.6f, 1.6f);
		m_Obstacles[i].obstacleTexture.reset(new VilagOS::Texture2D("assets/textures/Burazin.png"));
		m_Obstacles[i].rotation = 0.0f;
	}
	m_Obstacles[0].position = glm::vec3(5.0f, 5.0f, 0.0f);
	m_Obstacles[1].position = glm::vec3(3.0f, 3.0f, 0.0f);
}

void Level::LoadLevel() {
	CreateFloors();
	CreatePlatforms();
	CreateScripts();
	CreateObstacles();
}

bool Collided(glm::vec2 vert, glm::vec2 vertOne, glm::vec2 vertTwo, glm::vec2 vertThree, glm::vec2 vertFour) {
	float DOne = (vertTwo.x - vertOne.x) * (vert.y - vertOne.y) - (vert.x - vertOne.x) * (vertTwo.y - vertOne.y);
	float DTwo = (vertThree.x - vertTwo.x) * (vert.y - vertTwo.y) - (vert.x - vertTwo.x) * (vertThree.y - vertTwo.y);
	float DThree = (vertFour.x - vertThree.x) * (vert.y - vertThree.y) - (vert.x - vertThree.x) * (vertFour.y - vertThree.y);
	float DFour = (vertOne.x - vertFour.x) * (vert.y - vertFour.y) - (vert.x - vertFour.x) * (vertOne.y - vertFour.y);
	if (DOne >= 0 && DTwo >= 0 && DThree >= 0 && DFour >= 0) { return true; }
	else { return false; }
}

bool Level::OnPickup() {
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

	for (auto& script : m_Scripts) {
		

		glm::vec2 floorVerticies[4];

		for (int i = 0; i < 4; i++) {
			floorVerticies[i] = glm::translate(glm::mat4(1.0f), script.position) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(script.size.x, script.size.y, 1.0f)) * Verticies[i];
		}

		for (int j = 0; j < 4; j++) {
			if (Collided(glm::vec2(playerTransformedVerticies[j].x, playerTransformedVerticies[j].y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3])) {
				m_Index = script.index;
				return true;
			}
		}
	}

	return false;
}

bool Level::OnHit() {
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

	for (auto& script : m_Obstacles) {
		glm::vec2 floorVerticies[4];

		for (int i = 0; i < 4; i++) {
			floorVerticies[i] = glm::translate(glm::mat4(1.0f), script.position) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(script.size.x, script.size.y, 1.0f)) * Verticies[i];
		}

		for (int j = 0; j < 4; j++) {
			if (Collided(glm::vec2(playerTransformedVerticies[j].x, playerTransformedVerticies[j].y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3])) {
				return true;
			}
		}
	}

	return false;
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

	for (auto& floor : m_Floors) {
		
		glm::vec2 floorVerticies[4];
	
		for (int i = 0; i < 4; i++) {
			floorVerticies[i] = glm::translate(glm::mat4(1.0f), floor.position) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f) ,glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(floor.size.x, floor.size.y, 1.0f)) * Verticies[i];
		}
	
		for (auto vert : playerTransformedVerticies) {
			if (Collided(glm::vec2(vert.x, vert.y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3])) {
				return true;
			}
		}
	}

	for (auto& floor : m_FlyingStuff) {

		glm::vec2 floorVerticies[4];

		for (int i = 0; i < 4; i++) {
			floorVerticies[i] = glm::translate(glm::mat4(1.0f), floor.position) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(floor.size.x, floor.size.y, 1.0f)) * Verticies[i];
		}

		//for (int j = 1; j < 3; j++) {
			if (Collided(glm::vec2(playerTransformedVerticies[0].x, playerTransformedVerticies[0].y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3])) {
				return true;
			}
			if (Collided(glm::vec2(playerTransformedVerticies[3].x, playerTransformedVerticies[3].y), floorVerticies[0], floorVerticies[1], floorVerticies[2], floorVerticies[3])) {
				return true;
			}
		//}
	}

	return false;
}


