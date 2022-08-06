#pragma once

//Header 

#ifdef VOS_PLATFORM_WINDOWS

//Radimo ovo dinamièki pošto æe ovo biti cijela aplikacija tako da može biti jako veliko
extern VilagOS::Application* VilagOS::CreateApplication(); //defined in "GameApp" returns application

int main(int argc, char** argv) {
	VilagOS::Log::Init();
	VOS_CORE_WARN("Initialized Log");
	VOS_CLIENT_INFO("Hello");

	auto App = VilagOS::CreateApplication();
	App->run();
	delete App;
}

#endif // VOS_PLATFORM_WINDOWS
