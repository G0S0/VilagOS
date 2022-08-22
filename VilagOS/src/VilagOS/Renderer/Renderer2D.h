#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"

namespace VilagOS{
	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene() {};
		static void DrawQuad(const glm::vec2& position, glm::vec2 size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, glm::vec2 size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, glm::vec2 size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f);
		static void DrawQuad(const glm::vec3& position, glm::vec2 size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& position, glm::vec2 size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, glm::vec2 size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, glm::vec2 size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, glm::vec2 size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f);
	};
}