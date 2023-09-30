#include <iostream>
#include <unordered_map>

#include "../supernova/engine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"


using namespace std;
using namespace ImGui;



bool event_handler(SDL_Event &event) {
	ImGui_ImplSDL2_ProcessEvent(&event);
	return true;
}


int main(int argc, char* argv[]) {

	const int SCREENW = 800, SCREENH = 600;
	unordered_map<string, EventKey> EVENT_KEYS= {{"UP", {SDLK_UP}}};

	Window window("Dear ImGUI Demo", SCREENW, SCREENH);
	Renderer renderer(window);

	// Setup ImGUI
	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark(); // Setting theme
	ImGui_ImplSDL2_InitForSDLRenderer(window.window, renderer.renderer);
    ImGui_ImplSDLRenderer_Init(renderer.renderer);

	Clock clock;
	Events events;
	Mouse mouse{};

	bool running = true;
	double dt;

	while (running) {
		dt = clock.tick(60);

		events.process_events(running, EVENT_KEYS, mouse, event_handler);

		ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ShowDemoWindow();
        // Text((to_string(mouse.pos.x) + ", " + to_string(mouse.pos.y)).c_str()); 

        Render();
		renderer.clear({0, 0, 0});
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		renderer.present();
	}

    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    DestroyContext();

    return 0;
}
