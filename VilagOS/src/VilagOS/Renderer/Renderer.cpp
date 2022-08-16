#include "vospch.h"
#include "Renderer.h"


namespace VilagOS {
	void Renderer::BeginScene() {

	}

	void Renderer::EndScene() {

	}

	void Renderer::SubmitData(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->Bind();
		RenderCommand::DrawElements(vertexArray);
	}
}