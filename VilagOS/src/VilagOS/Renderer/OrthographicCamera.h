#pragma once
#include "glm/glm.hpp"

namespace VilagOS {
	class OrthographicCamera {
	public:
		OrthographicCamera() {}
		OrthographicCamera(float left, float right, float bottom, float top); //dont need near and far

		glm::vec3 GetPosition() { return m_Position; }
		inline void SetPosition(const glm::vec3& position) {
			m_Position = position; 
			RecalculateViewMatrix();
		}

		const inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		const inline glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		const inline float GetRotation() const { return m_rotation; }
			  

	private:
		void RecalculateViewMatrix();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix; //so that I dont have to do the calculations every time I need this matrix
		float m_rotation;

		glm::vec3 m_Position;

	};
}