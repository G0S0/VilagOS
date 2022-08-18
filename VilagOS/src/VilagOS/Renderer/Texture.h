#pragma once

namespace VilagOS {
	class Texture {
	public:
		virtual uint32_t GetWidth() const = 0; 
		virtual uint32_t GetGeight() const = 0;

		virtual void Bind() const = 0;
	};

	class Texture2D : public Texture {
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};
}