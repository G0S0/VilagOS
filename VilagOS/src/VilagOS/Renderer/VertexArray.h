#pragma once
#include "VilagOS/Core/Core.h"
#include "Buffer.h"
#include <memory>

namespace VilagOS {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray() {};

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer);
		void AddIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer);

		inline std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() { return m_VertexBuffers; }
		inline std::shared_ptr<IndexBuffer> GetIndexBuffer() { return m_indexBuffer; }

		inline VertexArray* GetThisVertexArray() { return this; }

	private: 
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
		uint32_t m_rendererID;
	};
}

