#pragma once
#include "VilagOS/Core/Layer.h"
#include "VilagOS/Events/KeyboardEvent.h"
#include "VilagOS/Events/MouseEvent.h"
#include "VilagOS/Events/ApplicationEvent.h"

namespace VilagOS {
	class VOS_API ImguiLayer: public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin(); //Begins ImGui rendering
		void End(); //Ends ImGui rendering
	private:
		float m_Time = 0.0f;
	};
}