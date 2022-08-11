#pragma once
#include "VilagOS/Layer.h"
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
		void OnKeyPressed();
		void OnKeyReleased();
		void OnMouseButtonPressed();
		void OnMouseButtonReleased();
		float m_Time = 0;
	};
}