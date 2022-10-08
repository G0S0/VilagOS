#pragma once

//Header 

#ifdef VOS_PLATFORM_WINDOWS
//Radimo ovo dinamički pošto će ovo biti cijela aplikacija tako da može biti jako veliko
extern VilagOS::Application* VilagOS::CreateApplication(); //defined in "GameApp" returns application

#ifdef VOS_RELEASE
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	VilagOS::Log::Init();
	VOS_CORE_WARN("Initialized Log");
	VOS_CLIENT_INFO("Hello");

	auto App = VilagOS::CreateApplication();
	App->run();
	delete App;
}
#else
int main(int argc, char** argv) {
	VilagOS::Log::Init();
	VOS_CORE_WARN("Initialized Log");
	VOS_CLIENT_INFO("Hello");

	auto App = VilagOS::CreateApplication();
	App->run();
	delete App;
}
#endif // VOS_RELEASE

#endif // VOS_PLATFORM_WINDOWS