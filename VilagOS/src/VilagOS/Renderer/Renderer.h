#pragma once

namespace VilagOS{
	enum class RendererAPI {
		None = 0, OpenGL = 1
	};

	class Renderer {
		static RendererAPI s_RendererAPI;
	};
}