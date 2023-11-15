#include <supernova/engine.h>
#include <supernova/constants.h>
#include <supernova/super_gui.h>


using namespace std;



int main(int argc, char* argv[]) {

	Engine engine;

	const IVector WINDOW_SIZE = {800, 600};

	Window window("ImGUI Demo", WINDOW_SIZE, SDL_WINDOW_RESIZABLE);
	Renderer renderer(window);

	Clock clock;
	Events events;

	DebugGUI gui(window, renderer);

	bool running = true;
	double dt;

	float scale = 0.5;
	IVector pos = {0, 0};

	Rect basic_rect = {0, 0, 100, 100};
	vector<Rect> rects;

	while (running) {
		dt = clock.tick(60);

		running = events.process_events(&EVENT_KEYS, nullptr, nullptr, gui.get_event_handler());

		gui.create_new_frame();

		ImGui::Begin("Debug Window");
		ImGui::Text("FPS: %i", int(clock.get_fps()));
		ImGui::InputInt("PosX", &pos.x);
		ImGui::InputInt("PosY", &pos.y);
		ImGui::SliderFloat("Scale", &scale, 0, 1);
		if (ImGui::Button("Add rect"))
			rects.push_back({pos.x, pos.y, static_cast<int>(100*scale), static_cast<int>(100*scale)});
		if (ImGui::Button("Quit"))
			running = false;
		ImGui::End();

		renderer.clear(WHITE);
		for (const Rect &rect: rects) {
			renderer.draw_rect(rect, RED);
		}
		gui.draw();
		renderer.present();
	}

	return 0;
}
