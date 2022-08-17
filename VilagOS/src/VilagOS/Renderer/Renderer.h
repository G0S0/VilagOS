#pragma once
#include "VilagOS/Renderer/Buffer.h"
#include "VertexArray.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace VilagOS{
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void static BeginScene(OrthographicCamera& Camera);
		void static EndScene();

		void static SubmitData(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

	private:
		struct SceneData {
			glm::mat4 m_ViewProjectionMatrix;// need this so that I can propagate it in submit data 
		};
		static SceneData* m_SceneData;
	};
}