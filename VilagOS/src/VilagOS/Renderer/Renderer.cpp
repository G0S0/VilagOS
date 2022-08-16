#include "vospch.h"
#include "Renderer.h"

namespace VilagOS {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& Camera) {
		m_SceneData->m_ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::SubmitData(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		shader->Bind();
		shader->UploadUniformMat4(m_SceneData->m_ViewProjectionMatrix, "u_ViewProjection");
		vertexArray->Bind();
		RenderCommand::DrawElements(vertexArray);
	}
}