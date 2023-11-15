#include <supernova/engine.h>


using namespace std;



int main(int argc, char* argv[]) {

	const IVector WINDOW_SIZE = {800, 600};

	Window window("Fog of War", WINDOW_SIZE);
	Renderer renderer(window);

	Texture bg_img(renderer, "image.png");
	Texture fow_tex(renderer, WINDOW_SIZE);

	Clock clock;
	Events events;
	Mouse mouse;

	bool running = true;
	double dt;

	fow_tex.set_blend_mode(SDL_BLENDMODE_MOD);

	while (running) {
		dt = clock.tick(60);

		running = events.process_events(nullptr, &mouse);

		renderer.clear({0, 0, 0});
		bg_img.render(bg_img.get_rect());

		renderer.set_target(fow_tex);
		renderer.clear({200, 200, 200, 255});
		renderer.draw_circle({mouse.pos, 100}, {255, 255, 255, 255});
		renderer.set_target();
		fow_tex.render(fow_tex.get_rect());

		renderer.present();
	}

    return 0;
}
