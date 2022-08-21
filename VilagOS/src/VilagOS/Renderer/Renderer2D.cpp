#include "vospch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace VilagOS {
	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> VertexArray;
		std::shared_ptr<Shader> FlatColorShader;
		std::shared_ptr<Shader> TextureShader;
	};

	static Renderer2DStorage s_Data; //Nema potrebe da ovo na heapu, eventualno ako struct bude imao još puno elemenata

	void Renderer2D::Init() {
		BufferLayout layout = { // layout setup
			{"a_Position", DataType::Float3}
		};

		BufferLayout textureLayout = { // layout setup
			{"a_Position", DataType::Float3},
			{"a_TextureCord", DataType::Float2}
		};
		
		s_Data.VertexArray.reset(new VertexArray());
		float Verticies[5 * 4] = {
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f 
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(new VertexBuffer(Verticies, sizeof(Verticies)));
		m_VertexBuffer->SetLayout(textureLayout);

		s_Data.VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t Indicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(new IndexBuffer(Indicies, sizeof(Indicies)));

		s_Data.VertexArray->AddIndexBuffer(m_IndexBuffer);

		s_Data.FlatColorShader.reset(new Shader("assets/shaders/FlatColor.glsl"));
		s_Data.TextureShader.reset(new Shader("assets/shaders/Texture.glsl"));
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->UploadUniformInt(0, "u_Texture");
	}
	void Renderer2D::Shutdown() {}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->UploadUniformMat4(camera.GetViewProjectionMatrix(), "u_ViewProjection");

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->UploadUniformMat4(camera.GetViewProjectionMatrix(), "u_ViewProjection");
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, glm::vec2 size, const glm::vec4& color) {
		Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, glm::vec2 size, const glm::vec4& color) {
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->UploadUniformVec4(color, "u_Color");

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * /* rotation*/ glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.FlatColorShader->UploadUniformMat4(transform, "u_Transform");
		
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, glm::vec2 size, const std::shared_ptr<Texture2D>& texture) {
		Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, glm::vec2 size, const std::shared_ptr<Texture2D>& texture){
		s_Data.TextureShader->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * /* rotation*/ glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.TextureShader->UploadUniformMat4(transform, "u_Transform");

		
		texture->Bind();
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

}

