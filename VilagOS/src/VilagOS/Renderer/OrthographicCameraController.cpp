#include "vospch.h"
#include "OrthographicCameraController.h"
#include "VilagOS/Input.h"
#include "VilagOS/KeyCodes.h"

namespace VilagOS {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio): 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_AspectRatio(aspectRatio) {}

	void OrthographicCameraController::OnUpdate(DeltaTime dt) {
		if (Input::IsKeyPressedStatic(VOS_KEY_A))
			m_CameraPosition.x -= m_CameraMovementSpeed * dt.GetMiliseconds();
		else if (Input::IsKeyPressedStatic(VOS_KEY_D))
			m_CameraPosition.x += m_CameraMovementSpeed * dt.GetMiliseconds();
		if (Input::IsKeyPressedStatic(VOS_KEY_W))
			m_CameraPosition.y += m_CameraMovementSpeed * dt.GetMiliseconds();
		else if (Input::IsKeyPressedStatic(VOS_KEY_S))
			m_CameraPosition.y -= m_CameraMovementSpeed * dt.GetMiliseconds();

		if (Input::IsKeyPressedStatic(VOS_KEY_Q))
			m_CameraRotation -= m_CameraRotationSpeed * dt.GetMiliseconds();
		if (Input::IsKeyPressedStatic(VOS_KEY_E))
			m_CameraRotation += m_CameraRotationSpeed * dt.GetMiliseconds();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}
	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(VOS_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch< WindowResizeEvent>(VOS_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizedEvent));
		
	}
	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e) { //changing the zoom level 
		m_ZoomLevel -= e.GetY() * 0.05f;
		VOS_CORE_TRACE(m_ZoomLevel);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResizedEvent(WindowResizeEvent& e) { //changing the aspect ratio
		m_AspectRatio = (float)e.getSizes().first / (float)e.getSizes().second; //problem je što kameru trenutno pickupa samo aspect ratio bez visine i širine.
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
