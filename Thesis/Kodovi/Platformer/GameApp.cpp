#include <VilagOS.h>
#include "imgui.h"
#include "DeltaTime.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VilagOS/Renderer/Shader.h"
#include "Game2D.h"
#include "VilagOS/Core/EntryPoint.h"

class Game : public VilagOS::Application {
public:
	Game() {
		PushLayer(new Game2D());
	}
	~Game() {}
};

VilagOS::Application* VilagOS::CreateApplication() {
	return new Game();
} 
