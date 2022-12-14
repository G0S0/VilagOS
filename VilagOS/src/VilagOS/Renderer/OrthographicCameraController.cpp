#include "vospch.h"
#include "OrthographicCameraController.h"
#include "VilagOS/Core/Input.h"
#include "VilagOS/Core/KeyCodes.h"

namespace VilagOS {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio): 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_AspectRatio(aspectRatio) {}

	OrthographicCameraController::OrthographicCameraController(float left, float right, float bottom, float top, float aspectRatio) :
		m_Camera(left, right, bottom, top), m_AspectRatio(aspectRatio) {}

	void OrthographicCameraController::OnUpdate(DeltaTime dt) {
		m_CameraPosition = m_Camera.GetPosition();
		if (Input::IsKeyPressedStatic(VOS_KEY_J))
			m_CameraPosition.x -= m_CameraMovementSpeed * dt.GetMiliseconds();
		else if (Input::IsKeyPressedStatic(VOS_KEY_L))
			m_CameraPosition.x += m_CameraMovementSpeed * dt.GetMiliseconds();
		if (Input::IsKeyPressedStatic(VOS_KEY_I))
			m_CameraPosition.y += m_CameraMovementSpeed * dt.GetMiliseconds();
		else if (Input::IsKeyPressedStatic(VOS_KEY_K))
			m_CameraPosition.y -= m_CameraMovementSpeed * dt.GetMiliseconds();
		
		m_Camera.SetPosition(m_CameraPosition);
	}
	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<MouseScrolledEvent>(VOS_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch< WindowResizeEvent>(VOS_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizedEvent));
		
	}
	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e) { //changing the zoom level 
		m_ZoomLevel -= e.GetY() * 0.05f;
		VOS_CORE_TRACE(m_ZoomLevel);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResizedEvent(WindowResizeEvent& e) { //changing the aspect ratio
		m_AspectRatio = (float)e.getSizes().first / (float)e.getSizes().second; //problem je ?to kameru trenutno pickupa samo aspect ratio bez visine i ?irine.
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
