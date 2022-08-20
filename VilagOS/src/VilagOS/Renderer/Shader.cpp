#include "vospch.h"
#include "Shader.h"
#include "Glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>

//TODO: remove


namespace VilagOS {
	Shader::Shader(const std::string& filepath) {
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	Shader::Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name(name) {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
		
	}

	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	std::string Shader::ReadFile(const std::string& filepath) {
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			VOS_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;

		VOS_CORE_ASSERT(type, "Invalid shader type!");
		return 0;
	}

	std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type"; //token for splitting the file
		size_t typeTokenLength = strlen(typeToken); 
		
		size_t pos = source.find(typeToken, 0);
		VOS_CORE_TRACE(pos);
		while (pos != std::string::npos) { //until the end of file
			size_t eol = source.find_first_of("\r\n", pos);
			VOS_CORE_ASSERT(eol != std::string::npos, "Syntax error. There are no more lines afer #type."); //ako nema linija nakon #type izbaci grešku
			size_t begin = pos + typeTokenLength + 1; //whitespace
			std::string type = source.substr(begin, eol - begin); //drugi dio linije
			VOS_CORE_ASSERT(type == "vertex" || type == "fragment", "Invalid shader type specified");
			size_t nextLinePos = source.find_last_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			std::string aux = source.substr(nextLinePos + 1, pos - nextLinePos - 1);
			shaderSources[ShaderTypeFromString(type)] = aux;
		}
		
		return shaderSources;
	}



	void Shader::Compile(std::unordered_map<GLenum, std::string> shaderSources) {
		GLuint program = glCreateProgram(); //I want my program to exist outside this constructor so im assigning it to a member variable
		VOS_CORE_ASSERT(shaderSources <= 2, "Since source codes are being alocated on stack the defines size of an array is 2 so you cant put in more than 2 source codes.");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		// Attach our shaders to our program
		
		for (auto& el : shaderSources) {
			GLenum type = el.first;
			const std::string& source = el.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled); //Checks if gl compiled successfully  m  
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				VOS_CORE_ERROR("Vertex shader compilation failure");
				VOS_CORE_ERROR("{0}", infoLog.data());
				// In this simple program, we'll just leave
				return;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for(auto id : glShaderIDs)
				glDeleteShader(id);

			// Use the infoLog as you see fit.
			VOS_CORE_ERROR("Shader link failure");
			VOS_CORE_ERROR("{0}", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}

	void Shader::Bind() const {
		glUseProgram(m_RendererID); //before starting rendering
	}

	void Shader::Unbind() const {
		glUseProgram(0); //before starting rendering
	}

	void Shader::UploadUniformMat4(const glm::mat4& matrix, const std::string& name) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::UploadUniformVec4(const glm::vec4& vec, const std::string& name) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::UploadUniformVec2(const glm::vec2& tex, const std::string& name) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, tex.x, tex.y);
	}

	void Shader::UploadUniformInt(const int tex, const std::string& name){
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, tex);
	}

	//Shader Library:

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader) {
		VOS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader) {
		auto& name = shader->GetName();
		ShaderLibrary::Add(name, shader);
	}

	std::shared_ptr < Shader > ShaderLibrary::Load(const std::string& filepath) {
		auto shader = std::shared_ptr<Shader>(new Shader(filepath));
		ShaderLibrary::Add(shader);
		return shader;
	}
	std::shared_ptr < Shader > ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = std::shared_ptr<Shader>(new Shader(filepath));
		ShaderLibrary::Add(name, shader);
		return shader;
	}
							  
	std::shared_ptr < Shader > ShaderLibrary::Get(const::std::string& name) {
		VOS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
		return m_Shaders[name];
	}

}