#include <supernova/engine.h>
#include <supernova/constants.h>


using namespace std;



int main(int argc, char* argv[]) {

	Engine engine;

	Window window("Basic Template", {800, 600});
	Renderer renderer(window);

	Clock clock;
	Events events;

	bool running = true;
	double dt;

	while (running) {
		dt = clock.tick(60);

		running = events.process_events();

		renderer.clear(WHITE);
		renderer.present();
	}

	return 0;
}
