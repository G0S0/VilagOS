#pragma once
#include "VilagOS/Renderer/Buffer.h"
#include "VertexArray.h"
#include "RenderCommand.h"

namespace VilagOS{
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void BeginScene();
		void EndScene();

		void static SubmitData(const std::shared_ptr<VertexArray>& vertexArray);
	};
}