#include <VilagOS.h>

class Game : public VilagOS::Application {
public:
	Game() {}
	~Game() {}
};

VilagOS::Application* VilagOS::CreateApplication() {
	return new Game();
}
