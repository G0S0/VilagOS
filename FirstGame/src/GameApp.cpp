#include <iostream>
#include <VilagOS.h>


class Game : public VilagOS::Application {
public:
	Game(){}
	~Game(){}
};

int main() {
	Game* App = new Game(); //Radimo ovo dinami�ki po�to �e ovo biti cijela aplikacija tako da mo�e biti jako veliko
	App->run();
	delete App;
}