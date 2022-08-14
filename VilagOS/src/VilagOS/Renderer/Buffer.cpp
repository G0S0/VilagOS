#include "vospch.h"
#include "Buffer.h"
#include "Glad/glad.h"

namespace VilagOS { //no members - pure virtual class just virtual functions there is no data here.
	VertexBuffer::VertexBuffer(float* verticies, uint32_t size) {
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererId);
	}

	void VertexBuffer::Bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void VertexBuffer::Unbind() const{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

