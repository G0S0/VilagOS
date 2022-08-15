#include "vospch.h"
#include "Buffer.h"
#include "Glad/glad.h"

namespace VilagOS { //no members - pure virtual class just virtual functions there is no data here.
	
	//VertexBuffer
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

	//IndexBuffer

	IndexBuffer::IndexBuffer(uint32_t* indicies, uint32_t count): m_Count(count) {
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_RendererId);
	}

	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void IndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

