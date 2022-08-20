#pragma once
#include <string>
#include "Glad/glad.h"
#include "glm/glm.hpp"

typedef unsigned int GLenum;

namespace VilagOS {
	class Shader {
	public: 
		//Takes source code for vertex and fragment shaders
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);
		void UploadUniformVec4(const glm::vec4& color, const std::string& name);
		void UploadUniformVec2(const glm::vec2& texcord, const std::string& name);
		void UploadUniformInt(const int tex, const std::string& name);

		inline uint32_t GetRendererId() { return m_RendererID; };

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source); // Idk how many files il need so im using unordered map
		void Compile(std::unordered_map<GLenum, std::string> ShaderSources);
		uint32_t m_RendererID;
	};
}