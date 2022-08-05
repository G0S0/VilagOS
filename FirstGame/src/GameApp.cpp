#include <iostream>
#include <VilagOS.h>


class Game : public VilagOS::Application {
public:
	Game(){}
	~Game(){}
};

int main() {
	Game* App = new Game(); //Radimo ovo dinamièki pošto æe ovo biti cijela aplikacija tako da može biti jako veliko
	App->run();
	delete App;
}