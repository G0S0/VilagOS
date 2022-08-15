#pragma once

namespace VilagOS {
	//VertexBuffer
	class VertexBuffer {
	public:
		VertexBuffer(float* verticies, uint32_t size);
		~VertexBuffer();
		void Bind() const;
		void Unbind() const;
		inline VertexBuffer* Get() { return this; };
	private:
		uint32_t m_RendererId;
	};

	//IndexBuffer
	class IndexBuffer {
	public:
		IndexBuffer(uint32_t* indicies, uint32_t size);
		~IndexBuffer();
		void Bind() const;
		void Unbind() const;
		inline uint32_t GetCount() const { return m_Count; };
		inline IndexBuffer* Get() { return this; };
	private:
		uint32_t m_RendererId;
		uint32_t m_Count;
	};

}