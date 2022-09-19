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

	if (m_Player.GetHp() <= 0) {
		m_GameOver = true;
	}

	if (m_Score == 7) {
		m_Victory = true;
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
		}
	}
	else {
		if (m_TimeElapsed - m_CountDown > 0.75f) {
			m_Flag = true;
		}
	}
	
	if (OnCollision()) {
		m_Player.SetInAir(false);
	}
	else {
		m_Player.SetInAir(true);
	}

	for (auto& el : m_Scripts) {
		el.rotation += 1.0f;
	}

	for (auto& obs : m_Obstacles) {
		obs.rotation += obs.speed * 90.0f * dt.GetMiliseconds();
		obs.position += obs.toChange * obs.speed * dt.GetMiliseconds();
		if (obs.orientation) {
			obs.travel = glm::distance(obs.position, obs.startPosition);
		}
		else {
			obs.travel = glm::distance(obs.position, obs.destination);
		}
		//VOS_CLIENT_INFO("{0}, {1}, {2}, {3}", obs.toTravel, obs.travel, obs.position.x, obs.position.y);
		if(obs.toTravel < obs.travel){
			obs.speed *= -1;
			obs.orientation = !obs.orientation;
		}
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
	m_GameOver = false;
	m_Flag = true;
	m_Score = 0;
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
	m_FlyingStuff.resize(13);
	for (auto& el : m_FlyingStuff) {
		el.grassTexture.reset(new VilagOS::Texture2D("assets/textures/grass.png"));
	}
	m_FlyingStuff[0].position = glm::vec3(3.0f, -1.0f, -0.3f);
	m_FlyingStuff[0].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[1].position = glm::vec3(8.0f, 4.0f, -0.3f);
	m_FlyingStuff[1].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[2].position = glm::vec3(23.0f, 10.0f, -0.3f);
	m_FlyingStuff[2].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[3].position = glm::vec3(-1.5f, 7.3f, -0.3f);
	m_FlyingStuff[3].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[4].position = glm::vec3(-12.0f, 15.0f, -0.3f);
	m_FlyingStuff[4].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[5].position = glm::vec3(3.5f, 20.0f, -0.3f);
	m_FlyingStuff[5].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[6].position = glm::vec3(14.5f, 27.0f, -0.3f);
	m_FlyingStuff[6].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[7].position = glm::vec3(30.5f, 27.0f, -0.3f);
	m_FlyingStuff[7].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[8].position = glm::vec3(40.0f, 20.0f, -0.3f);
	m_FlyingStuff[8].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[9].position = glm::vec3(53.0f, 30.0f, -0.3f);
	m_FlyingStuff[9].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[10].position = glm::vec3(35.0f, 6.0f, -0.3f);
	m_FlyingStuff[10].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[11].position = glm::vec3(47.0f, 0.0f, -0.3f);
	m_FlyingStuff[11].size = glm::vec2(5.1f, 0.9f);

	m_FlyingStuff[12].position = glm::vec3(50.0f, 12.0f, -0.3f);
	m_FlyingStuff[12].size = glm::vec2(5.1f, 0.9f);
}

void Level::CreateScripts() {
	m_Scripts.resize(7);

	for (int i = 0; i < m_Scripts.size(); i++) {
		m_Scripts[i].size = glm::vec2(1.5f, 1.4f*1.5f);
		m_Scripts[i].rotation = 0.0f;
		m_Scripts[i].scriptTexture.reset(new VilagOS::Texture2D("assets/textures/script.png"));
		m_Scripts[i].index = i;
	}
	m_Scripts[0].position = glm::vec3(-3.0f, -3.5f, -0.2f);
	m_Scripts[1].position = glm::vec3(55.0f, -3.5f, -0.2f);
	m_Scripts[2].position = glm::vec3(-12.0f, 17.5f, -0.3f);
	m_Scripts[3].position = glm::vec3(23.0f, 12.5f, -0.3f);
	m_Scripts[4].position = glm::vec3(35.0f, 8.5f, -0.3f);
	m_Scripts[5].position = glm::vec3(23.0f, 27.0f, -0.3f);
	m_Scripts[6].position = glm::vec3(53.0f, 32.0f, -0.3f);

}

void Level::CreateObstacles() {
	m_Obstacles.resize(8);
	m_Obstacles[0].position = glm::vec3(56.5f, -4.0f, 0.0f);
	m_Obstacles[0].destination = glm::vec3(-15.0f, -4.0f, 0.0f);
	m_Obstacles[0].toChange = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Obstacles[0].speed = 10.0f;
	
	m_Obstacles[1].position = glm::vec3(-1.5f, 7.3f, 0.0f);
	m_Obstacles[1].destination = glm::vec3(-4.0f, 25.0f, 0.0f);
	m_Obstacles[1].toChange = glm::vec3(0.0, 1.0f, 0.0f);
	m_Obstacles[1].speed = 12.0f;
	
	m_Obstacles[2].position = glm::vec3(35.6f, 26.5f, 0.0f);
	m_Obstacles[2].destination = glm::vec3(55.5f, 26.5f, 0.0f);
	m_Obstacles[2].toChange = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Obstacles[2].speed = 12.0f;
	
	m_Obstacles[3].position = glm::vec3(25.5f, 29.5f, 0.0f); //gore
	m_Obstacles[3].destination = glm::vec3(19.0f, 27.0f, 0.0f);
	m_Obstacles[3].toChange = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Obstacles[3].speed = 8.0f;
	
	
	m_Obstacles[4].position = glm::vec3(25.5f, 29.5f, 0.0f); //desno
	m_Obstacles[4].destination = glm::vec3(25.5f, 24.5f, 0.0f);
	m_Obstacles[4].toChange = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Obstacles[4].speed = 8.0f;
	
	
	m_Obstacles[5].position = glm::vec3(19.0f, 24.5f, 0.0f); //dolje
	m_Obstacles[5].destination = glm::vec3(25.5f, 26.5f, 0.0f);
	m_Obstacles[5].toChange = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Obstacles[5].speed = 8.0f;
	
	
	m_Obstacles[6].position = glm::vec3(19.0f, 24.5f, 0.0f); //lijevo
	m_Obstacles[6].destination = glm::vec3(19.0f, 29.5f, 0.0f);
	m_Obstacles[6].toChange = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Obstacles[6].speed = 8.0f;

	m_Obstacles[7].position = glm::vec3(56.5f, 34.5f, 0.0f);
	m_Obstacles[7].destination = glm::vec3(-15.25, -4.25f, 0.0f);
	m_Obstacles[7].toChange = glm::vec3(1.0f * 1.77777778f, 1.0f, 0.0f);
	m_Obstacles[7].speed = 5.0f;


	for (int i = 0; i < m_Obstacles.size(); i++) {
		m_Obstacles[i].size = glm::vec2(1.6f, 1.6f);
		m_Obstacles[i].obstacleTexture.reset(new VilagOS::Texture2D("assets/textures/Burazin.png"));
		m_Obstacles[i].rotation = 0.0f;
		m_Obstacles[i].startPosition = m_Obstacles[i].position;
		m_Obstacles[i].travel = 0.0f;
		m_Obstacles[i].toTravel = glm::distance(m_Obstacles[i].startPosition, m_Obstacles[i].destination);
		m_Obstacles[i].orientation = true;
		if (glm::dot(m_Obstacles[i].startPosition, m_Obstacles[i].toChange) > glm::dot(m_Obstacles[i].destination, m_Obstacles[i].toChange)) {
			m_Obstacles[i].speed *= -1.0f;
		}
	}
}

void Level::LoadLevel() {
	CreateFloors();
	CreatePlatforms();
	CreateScripts();
	CreateObstacles();
	m_Score = 0;
	m_Victory = false;
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


