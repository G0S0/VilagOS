#include "vospch.h"
#include <string>
#include "Texture.h"
#include "Glad/glad.h"
#include "stb/stb_image.h"

namespace VilagOS {
	Texture2D::Texture2D(const std::string& path) : m_Path(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(0); //Idk why this suddenly had to switch from 1 to 0 but it was after I added the camera controls.
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		VOS_CORE_ASSERT(data, "Failed to load image");
		m_Width = width;
		m_Height = height;

		GLenum openGlFormat = 0, dataFormat = 0;
		if (channels == 4) {
			openGlFormat = GL_RGBA8;
			dataFormat = GL_RGBA;

		}
		else if (channels == 3) {
			openGlFormat = GL_RGBA8;
			dataFormat = GL_RGB;
		}

		VOS_CORE_ASSERT(openGlFormat && dataFormat, "Format not supported!");
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		//Memory allocation
		glTextureStorage2D(m_RendererId, 1, openGlFormat, m_Width, m_Height);
		
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//Uploading the texture
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		//Since data is on gpu I can delete it from cpu memmory
		stbi_image_free(data); //takes pointer to data and frees it form memory
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_RendererId);
	}

	void Texture2D::Bind(uint32_t slot) const{
		glBindTextureUnit(slot, m_RendererId);
	}
}