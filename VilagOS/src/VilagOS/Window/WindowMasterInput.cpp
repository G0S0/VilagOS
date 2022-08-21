#include "vospch.h"
#include "WindowMasterInput.h"
#include "glfw3.h"
#include "VilagOS/Core/Application.h"

namespace VilagOS {
	Input* Input::s_Instance = new WindowMasterInput();

	bool WindowMasterInput::IsKeyPressed(int keycode) {
		auto window = static_cast <GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowMasterInput::IsMouseButtonPressed(int button) {
		auto window = static_cast <GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowMasterInput::GetMousePosition() {
		auto window = static_cast <GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::make_pair((float)xpos, (float)ypos);
	}
}