#pragma once

#include "VilagOS/Events/Event.h"
#include "VilagOS/Core/DeltaTime.h"

namespace VilagOS {
	//Interface
	class VOS_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer(); //Need a virtual destroctor because this is going to be subclassed

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(DeltaTime DeltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}