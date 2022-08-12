#pragma once
#include "VilagOS/Core.h"
#include <utility>
 
namespace VilagOS {
	class VOS_API Input {
	public:
		inline static bool IsKeyPressedStatic(int keycode) { return s_Instance->IsKeyPressed(keycode); };
		inline static bool IsMouseButtonPressedStatic(int button) { return s_Instance->IsKeyPressed(button); };
		inline static std::pair<float, float> GetMousePositionStatic() { return s_Instance->GetMousePosition(); };
	protected:
		virtual bool IsKeyPressed(int keycode) = 0;
		virtual bool IsMouseButtonPressed(int button) = 0;
		virtual std::pair<float, float> GetMousePosition() = 0;
	private:
		static Input* s_Instance;
	};
}