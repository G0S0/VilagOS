#include "vospch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace VilagOS {
	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> VertexArray;
		std::shared_ptr<Shader> FlatColorShader;
	};

	static Renderer2DStorage s_Data; //Nema potrebe da ovo na heapu, eventualno ako struct bude imao još puno elemenata

	void Renderer2D::Init() {
		BufferLayout layout = { // layout setup
			{"a_Position", DataType::Float3}
		};
		
		s_Data.VertexArray.reset(new VertexArray());
		float Verticies[3 * 4] = {
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(new VertexBuffer(Verticies, sizeof(Verticies)));
		m_VertexBuffer->SetLayout(layout);

		s_Data.VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t Indicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(new IndexBuffer(Indicies, sizeof(Indicies)));

		s_Data.VertexArray->AddIndexBuffer(m_IndexBuffer);

		s_Data.FlatColorShader.reset(new Shader("assets/shaders/FlatColor.glsl"));
	}
	void Renderer2D::Shutdown() {}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->UploadUniformMat4(camera.GetViewProjectionMatrix(), "u_ViewProjection");
		s_Data.FlatColorShader->UploadUniformMat4(glm::mat4(1.0f), "u_Transform");
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, glm::vec2 size, const glm::vec4& color) {
		Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, glm::vec2 size, const glm::vec4& color) {
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->UploadUniformVec4(color, "u_Color");
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

}

