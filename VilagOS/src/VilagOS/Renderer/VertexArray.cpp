#include "vospch.h"

#include "VertexArray.h"
#include "glad.h"
#include "Buffer.h" //to get DataType function

namespace VilagOS {

	VertexArray::VertexArray() {
		glCreateVertexArrays(1, &m_rendererID);
	}

	void VertexArray::Bind() const{
		glBindVertexArray(m_rendererID);
	}

	void VertexArray::Unbind() const{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer){
		glBindVertexArray(m_rendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		auto& layout = vertexBuffer->GetBufferLayout();
		for (auto& it : layout.GetBufferElements()) {//setting up vertexbuffer
			glEnableVertexAttribArray(index);
			//On index (index) there are (it.GetComponentCount()) float verticies, that are (it.Normalized), 
			//the stride between each vertex is (GetDataTypeSize()) bytes, and the offset is (it.Offset) bytes
			//glVertexAttribPointer(index, it.GetComponentCount(), GL_FLOAT, it.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)it.Offset);
			glVertexAttribPointer(index, it.GetComponentCount(), GL_FLOAT, it.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride() , (const void*)it.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	
	void VertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer){
		glBindVertexArray(m_rendererID);
		indexBuffer->Bind();
		m_indexBuffer = indexBuffer;
	}
}