#include <supernova/core.h>
#include <supernova/logging.h>
#include <supernova/constants.h>
#include <supernova/supershader.h>


using namespace std;



int main(int argc, char *argv[]) {
	Engine engine;

	GLCanvas::set_attributes();

	Window window("Shader Demo", {800, 600});
	Renderer renderer(window, 0, "opengl");

	Clock clock;
	Events events;

	bool rng = true;
	double dt;
	int c = 0;

	Texture tex(renderer, "SDL_logo.png");
	Rect rect = tex.get_rect();
	rect.scale(2.0f);
	rect.center({400, 300});

	GLCanvas canvas({800, 600}, window, renderer);
	Shader shaders[2] = {
		Shader("shader.vert", "grayscale_shader.frag"),
		Shader("shader.vert", "rgb_shader.frag")
	};
	
	EventKeys event_keys = {
		{"NEXT", {SDLK_SPACE}}
	};

	while (rng) {
		dt = clock.tick(60);

		rng = events.process_events(&event_keys);

		if (event_keys["NEXT"].pressed) {
			c = (c + 1)%2;
		}

		canvas.begin();
		renderer.clear(WHITE);
		tex.render(rect);
		canvas.draw(shaders[c]);
	}

	return 0;
}

