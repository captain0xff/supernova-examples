#include <supernova/engine.h>
#include <supernova/constants.h>
#include <supernova/enums.h>


using namespace std;



int main(int, char**) {

	Engine engine;

	Window window("Font example", {800, 600});
	Renderer renderer(window);

	Clock clock;
	Events events;

	bool running = true;
	double dt, volume;

	Font font("font.ttf", 30);
	font.wrap_alignment(TTF_WRAPPED_ALIGN_CENTER);
	Texture static_text = font.create_text(renderer, "Font Example\nSDL Powered", GREEN);
	Rect static_text_rect = static_text.get_rect();
	static_text_rect.size(static_text_rect.size());
	static_text_rect.center({400, 300});
	auto atlas = font.create_atlas(renderer, BLUE);

	while (running) {
		dt = clock.tick(60);

		running = events.process_events();

		renderer.clear({0, 0, 0});
		static_text.render(static_text_rect);
		atlas.draw_text("FPS: " + to_string(int(clock.get_fps())), {0, 0});
		renderer.present();
	}

	return 0;
}
