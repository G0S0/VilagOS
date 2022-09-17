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
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage s_Data; //Nema potrebe da ovo na heapu, eventualno ako struct bude imao još puno elemenata

	void Renderer2D::Init() {
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

		s_Data.WhiteTexture.reset(new Texture2D(1, 1));
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		//s_Data.Shader.reset(new Shader("assets/shaders/FlatColor.glsl"));
		s_Data.Shader.reset(new Shader("assets/shaders/Texture.glsl"));
		s_Data.Shader->Bind();
		s_Data.Shader->UploadUniformInt(0, "u_Texture");
	}
	void Renderer2D::Shutdown() {}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data.Shader->Bind();
		s_Data.Shader->UploadUniformMat4(camera.GetViewProjectionMatrix(), "u_ViewProjection");
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, glm::vec2 size, const glm::vec4& color) {
		Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, glm::vec2 size, const glm::vec4& color) {
		s_Data.Shader->UploadUniformVec4(color, "u_Color");
		s_Data.Shader->UploadUniformFloat(1.0f, "u_Tiling");
		s_Data.WhiteTexture->Bind();
		

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.Shader->UploadUniformMat4(transform, "u_Transform");
		
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, glm::vec2 size, const std::shared_ptr<Texture2D>& texture, float tiling) {
		Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, texture, tiling);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, glm::vec2 size, const std::shared_ptr<Texture2D>& texture, float tiling){
		//s_Data.Shader->Bind();
		s_Data.Shader->UploadUniformVec4(glm::vec4(1.0f), "u_Color");
		s_Data.Shader->UploadUniformFloat(tiling, "u_Tiling");
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.Shader->UploadUniformMat4(transform, "u_Transform");

		
		texture->Bind();
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, glm::vec2 size, float rotation, const glm::vec4& color) {
		Renderer2D::DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, glm::vec2 size, float rotation, const glm::vec4& color) {
		s_Data.Shader->UploadUniformVec4(color, "u_Color");
		s_Data.Shader->UploadUniformFloat(1.0f, "u_Tiling");
		s_Data.WhiteTexture->Bind();


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.Shader->UploadUniformMat4(transform, "u_Transform");

		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, glm::vec2 size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling) {
		Renderer2D::DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tiling);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, glm::vec2 size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling) {
		s_Data.Shader->UploadUniformVec4(glm::vec4(1.0f), "u_Color");
		s_Data.Shader->UploadUniformFloat(tiling, "u_Tiling");
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.Shader->UploadUniformMat4(transform, "u_Transform");


		texture->Bind();
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

	void Renderer2D::DrawRotatedQuadZ(const glm::vec3& position, glm::vec2 size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling) {
		s_Data.Shader->UploadUniformVec4(glm::vec4(1.0f), "u_Color");
		s_Data.Shader->UploadUniformFloat(tiling, "u_Tiling");
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 1.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data.Shader->UploadUniformMat4(transform, "u_Transform");


		texture->Bind();
		s_Data.VertexArray->Bind();
		RenderCommand::DrawElements(s_Data.VertexArray);
	}

}

