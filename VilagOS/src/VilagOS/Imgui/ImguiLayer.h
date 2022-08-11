#pragma once
#include "VilagOS/Layer.h"
#include "VilagOS/Events/KeyboardEvent.h"
#include "VilagOS/Events/MouseEvent.h"
#include "VilagOS/Events/ApplicationEvent.h"
#include "VilagOS/Events/Event.h"

namespace VilagOS {
	class VOS_API ImguiLayer: public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private: 
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& r);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		float m_Time = 0.0f;
	};
}