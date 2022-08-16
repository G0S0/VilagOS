#pragma once
#include <vector>
#include "VilagOS/Core.h"

namespace VilagOS {

	enum class DataType
	{
		None = 0, Float3, Float4
	};

	static uint32_t GetDataTypeSize(DataType type) {
		switch (type)
		{
		case DataType::Float3:
			return 4 * 3;
			break;
		case DataType::Float4:
			return 4 * 4;
			break;
		default:
			VOS_CORE_ASSERT(false, "Unknown Data type!");
			break;
		}
	}

	struct BufferElement {
		std::string Name;
		DataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement(const std::string& name, DataType type, bool normalized = false) : 
			Name(name), Type(type), Size(GetDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		BufferElement() {}

		uint32_t GetComponentCount() const{
			switch (Type)
			{
			case VilagOS::DataType::Float3:
				return 3;
			case VilagOS::DataType::Float4:
				return 4;
			}
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout(){}

		BufferLayout(const std::initializer_list<BufferElement>& elements) :m_Elements(elements) {
			CalculateOffsetsAndStride();
		}
		inline const std::vector<BufferElement>& GetBufferElements() const { return m_Elements; };
		inline const  uint32_t GetStride() const { return m_Stride; }
		
	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	//VertexBuffer
	class VertexBuffer {
	public:
		VertexBuffer(float* verticies, uint32_t size);
		~VertexBuffer();
		void Bind() const;
		void Unbind() const;

		// maybe I shouldve set it the other way around so that Layout encapsulates buffer. 
		inline const BufferLayout& GetBufferLayout() const { return m_Layout; }
		inline void SetLayout(BufferLayout layout) { m_Layout = layout; }

		inline VertexBuffer* Get() { return this; };
	private:
		uint32_t m_RendererId;
		BufferLayout m_Layout;
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