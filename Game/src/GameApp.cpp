#include <VilagOS.h>

class ExampleLayer : public VilagOS::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnImGuiRender() override {
		//VOS_CLIENT_INFO("Example layer: update");
		if(VilagOS::Input::IsKeyPressedStatic(VOS_KEY_TAB))
			VOS_CLIENT_TRACE("Tab key is pressed");
	}

	void OnEvent(VilagOS::Event& e) override {
		//VOS_CLIENT_INFO("Event: {0}", e);
	}
};

class Game : public VilagOS::Application {
public:
	Game() {
		
		PushLayer(new ExampleLayer());
	}
	~Game() {}
};

VilagOS::Application* VilagOS::CreateApplication() {
	return new Game();
}
