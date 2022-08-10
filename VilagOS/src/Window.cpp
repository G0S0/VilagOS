#include "vospch.h"
#include "Window.h"
#include "VilagOS/Core.h"
#include "VilagOS/Events/ApplicationEvent.h"
#include "VilagOS/Events/KeyboardEvent.h"
#include "VilagOS/Events/MouseEvent.h"

namespace VilagOS {
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallBack(int error, const char* description){
		VOS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
			VOS_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallBack);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//GLFW callbacks:
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);

		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetx, double offsety) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)offsetx, (float)offsety);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double posx, double posy) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)posx, (float)posy);
			data.EventCallback(event);
		});

	}

	void Window::Shutdown() {
		glfwDestroyWindow(m_Window);
	}
}