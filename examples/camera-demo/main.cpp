#include <supernova/core.h>
#include <supernova/logging.h>
#include <supernova/constants.h>


using namespace std;



int main(int argc, char *argv[]) {
	Engine engine;

	Window window("Camera Demo", {800, 600});
	Renderer renderer(window, (SDL_RendererFlags)0, "software");

	Clock clock;
	Events events;

	bool rng = true;
	double dt;

	Camera camera;

	while (rng) {
		dt = clock.tick(60);

		rng = events.process_events(&EVENT_KEYS);

		if (camera.is_new_frame_available()) {
			Texture tex(renderer, camera.acquire_frame());
			tex.render({0, 0, 800, 600});
			camera.release_frame();
		}
		
		renderer.present();
	}

	return 0;
}

