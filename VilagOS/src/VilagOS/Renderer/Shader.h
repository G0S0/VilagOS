#pragma once
#include <string>
#include "Glad/glad.h"
#include "glm/glm.hpp"

typedef unsigned int GLenum;

namespace VilagOS {
	class Shader {
	public: 
		//Takes source code for vertex and fragment shaders
		Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);
		void UploadUniformVec4(const glm::vec4& color, const std::string& name);
		void UploadUniformVec2(const glm::vec2& texcord, const std::string& name);
		void UploadUniformInt(const int tex, const std::string& name);
		void UploadUniformFloat(const float ft, const std::string& name);

		inline uint32_t GetRendererId() { return m_RendererID; }
		inline const std::string& GetName() { return m_Name; }

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source); // Idk how many files il need so im using unordered map
		void Compile(std::unordered_map<GLenum, std::string> ShaderSources);
		uint32_t m_RendererID;
		std::string m_Name;
	};

	class ShaderLibrary {
	public:
		void Add(const std::shared_ptr < Shader >& shader);
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		std::shared_ptr < Shader > Load(const std::string& filepath);
		std::shared_ptr < Shader > Load(const std::string& name, const std::string& filepath);

		std::shared_ptr < Shader > Get(const::std::string& name);
	private:
		std::unordered_map < std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}