#define SCREENW 800
#define SCREENH 600

#define WIN_32_LEAN_AND_MEAN
#include <windows.h>
#include <sfml/Graphics.hpp>

#include "../supernova/engine.h"

#include <SDL2/SDL_syswm.h>


using namespace std;



int main() {

	Engine engine;

	Window window("SFML demo", SCREENW, SCREENH);
	Renderer renderer(window);

	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(window.window, &info);
	HWND hwnd = info.info.win.window;

	sf::RenderWindow win(hwnd);
	sf::Shader shader;
	shader.loadFromFile("shader.frag", sf::Shader::Fragment);

    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Green);

	Clock clock;
	Events events;

	EVENT_KEYS["UP"] = {SDLK_UP};

	bool running = true;
	double dt;

	while (running) {
		dt = clock.tick(60);

		running = events.process_events(&EVENT_KEYS);

		win.clear();
		win.draw(shape, &shader);
		win.display();
	}

	Quit();

    return 0;
}
