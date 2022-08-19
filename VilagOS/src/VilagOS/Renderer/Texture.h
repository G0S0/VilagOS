#pragma once

namespace VilagOS {
	class Texture {
	public:

		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0; 
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture {
	public:
		Texture2D(const std::string& path);
		~Texture2D();

		inline uint32_t GetHeight() const override { return m_Height; }
		inline uint32_t GetWidth() const override { return m_Width; }
		void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererId;
	};
}