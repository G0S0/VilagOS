#pragma once
#include "VilagOS/Core/Input.h"

namespace VilagOS {
	class WindowMasterInput: public Input{
	protected:
		virtual bool IsKeyPressed(int keycode) override;
		virtual bool IsMouseButtonPressed(int button) override;
		virtual std::pair<float, float> GetMousePosition() override;
	};
}