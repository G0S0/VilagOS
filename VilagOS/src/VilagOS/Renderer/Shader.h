#pragma once
#include <string>


namespace VilagOS {
	class Shader {
	public: 
		//Takes source code for vertex and fragment shaders
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}