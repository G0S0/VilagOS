#pragma once
#include "VertexArray.h"
#include "Glad/glad.h"
#include "glm/glm.hpp"

namespace VilagOS {
	class RenderCommand {
	public:
		inline static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray) {
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

		static void Clear(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};
}