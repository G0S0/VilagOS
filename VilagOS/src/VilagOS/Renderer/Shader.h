#pragma once
#include <string>
#include "glm/glm.hpp"

namespace VilagOS {
	class Shader {
	public: 
		//Takes source code for vertex and fragment shaders
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);
		void UploadUniformVec4(const glm::vec4& color, const std::string& name);

		inline uint32_t GetRendererId() { return m_RendererID; };

	private:
		uint32_t m_RendererID;
	};
}