#include <supernova/engine.h>
#include <supernova/constants.h>
#include <supernova/super_gui.h>


using namespace std;



class GUI: public DebugGUI {
	public:
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

		GUI(Window &window, Renderer &renderer);

		void update(const IVector &window_size);
};

GUI::GUI(Window &window, Renderer &renderer): DebugGUI(window, renderer) {
	// Disable the ini file
	io->IniFilename = NULL;
	io->LogFilename = NULL;
}

void GUI::update(const IVector &window_size) {
	create_new_frame();

	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize(
		{static_cast<float>(window_size.x), static_cast<float>(window_size.y)/5}
	);

	ImGui::Begin("Menu", NULL, flags);
	ImGui::Text("Cool");
	ImGui::End();
}



int main(int argc, char* argv[]) {

	Engine engine;

	IVector window_size = {800, 600};

	Window window("ImGUI Demo", window_size, SDL_WINDOW_RESIZABLE);
	Renderer renderer(window);

	Clock clock;
	Events events;

	GUI gui(window, renderer);

	auto event_handler = [&window_size, &gui](SDL_Event &event) {
		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				window_size.x = event.window.data1;
				window_size.y = event.window.data2;
			}
		}

		gui.process_events(event);

		return false;
	};

	bool running = true;
	double dt;

	float scale = 0.5;
	IVector pos = {0, 0};

	Rect basic_rect = {0, 0, 100, 100};
	vector<Rect> rects;

	while (running) {
		dt = clock.tick(60);

		running = events.process_events(&EVENT_KEYS, nullptr, nullptr, event_handler);

		gui.update(window_size);

		renderer.clear(WHITE);
		for (const Rect &rect: rects) {
			renderer.draw_rect(rect, RED);
		}
		gui.draw();
		renderer.present();
	}

	return 0;
}
