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
	private:
		uint32_t m_RendererID;
	};
}