#pragma once
#include "VertexArray.h"
#include "glm/glm.hpp"
#include "Glad/glad.h"

namespace VilagOS {
	class RenderCommand {
	public:
		void  static Init() { //what does this do?
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		inline static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray) {
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			glViewport(x, y, width, height);
		}

		static void Clear(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};
}