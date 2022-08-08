#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace VilagOS{
	Application::Application() {

	}
	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		VOS_CLIENT_TRACE(e.ToPrint()); //this should work without ToPrint() function but overloaded operator doesnt work properly
		while (true);
	}
}