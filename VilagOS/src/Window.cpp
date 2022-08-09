#include "vospch.h"
#include "Window.h"
#include "VilagOS/Core.h"

namespace VilagOS {
	static bool s_GLFWInitialized = false;


	WindowMaster* WindowMaster::Create(const WindowProps& props) {
		return new Window(props);
	}

	Window::Window(const WindowProps& props) {
		Init(props);
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::OnUpdate() {
		glfwPollEvents(); //what does this do?
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}
	
	bool Window::IsVSync() const{
		return m_Data.VSync;
	}

	void Window::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		if (!s_GLFWInitialized) {
			int success = glfwInit();//why is this like this again?
			VOS_CORE_ASSERT(success, "GLFW")
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void Window::Shutdown() {
		glfwDestroyWindow(m_Window);
	}
}