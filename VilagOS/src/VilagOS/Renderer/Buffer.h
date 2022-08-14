#pragma once

namespace VilagOS {
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

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() = 0;
		virtual void Ubind() = 0;

		static IndexBuffer* Create(float* indicies, uint32_t size);
	
	};

}