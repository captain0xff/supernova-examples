#include <supernova/core.h>
#include <supernova/constants.h>
#include <supernova/supergui.h>
#include <supernova/supershader.h>

#include "gl.h"

#include "default_shaders.h"


using namespace std;



class GUI: public DebugGUI {
	public:
		char vert_buffer[64000];
		char frag_buffer[64000];
		char *vert_error, *frag_error, *link_error;

		bool run;
		bool error_tab = false;

		GUI(Window &window, Renderer &renderer);

		void update();
};

GUI::GUI(Window &window, Renderer &renderer): DebugGUI(window, renderer) {
	io->IniFilename = NULL;
	io->LogFilename = NULL;

	SDL_StartTextInput();

	strcpy(vert_buffer, DEFAULT_VERTEX_SHADER);
	strcpy(frag_buffer, DEFAULT_FRAGMENT_SHADER);
}

void GUI::update() {
	create_new_frame();

	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({800, 600});

	ImGui::Begin(
		"##Editor",
		NULL,
		ImGuiWindowFlags_NoTitleBar
			|ImGuiWindowFlags_NoCollapse
			|ImGuiWindowFlags_NoResize
			|ImGuiWindowFlags_NoMove
	);
	if (ImGui::BeginTabBar("Tab")) {
		if (ImGui::BeginTabItem("Vertex Shader")) {
			ImGui::InputTextMultiline("##VERT", vert_buffer, 64000, {-1, -100}, ImGuiInputTextFlags_AllowTabInput);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Fragment Shader")) {
			ImGui::InputTextMultiline("##FRAG", frag_buffer, 64000, {-1, -100}, ImGuiInputTextFlags_AllowTabInput);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Error", &error_tab)) {
			ImGui::InputTextMultiline("##VE", vert_error, 2048, {-1, 0}, ImGuiInputTextFlags_ReadOnly);
			ImGui::InputTextMultiline("##FE", frag_error, 2048, {-1, 0}, ImGuiInputTextFlags_ReadOnly);
			ImGui::InputTextMultiline("##LE", link_error, 2048, {-1, 0}, ImGuiInputTextFlags_ReadOnly);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	run = ImGui::Button("Run");
	ImGui::End();
}


class HotShader: public Shader {
	public:
		bool compile_status = true;
		char vert_error_buffer[2048] = {'\0'};
		char frag_error_buffer[2048] = {'\0'};
		char link_error_buffer[2048] = {'\0'};

		// Loads the shader from memory
		HotShader(
			const char *vertex_shader,
			const char *fragment_shader
		);

		void compile_shader(
			const char *vertex_shader_source,
			const char *fragment_shader_source
		);

		void reset_error_buffers();
};

HotShader::HotShader(const char *vertex_shader, const char *fragment_shader):
	Shader(vertex_shader, fragment_shader, false) {}


void HotShader::compile_shader(const char *vertex_shader_source, const char *fragment_shader_source) {
	int success;
	GLint new_id;

	compile_status = true;

	// Compile the vertex shader
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 2048, NULL, vert_error_buffer);
		compile_status = false;
		return;
	}

	// Compile the fragment shader
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 2048, NULL, frag_error_buffer);
		compile_status = false;
		return;
	}

	// Create the shader program and link it
	new_id = glCreateProgram();
	glAttachShader(new_id, vertex_shader);
	glAttachShader(new_id, fragment_shader);
	glLinkProgram(new_id);

	// Check if the shader program linked successfully
	glGetProgramiv(new_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(new_id, 512, NULL, link_error_buffer);
		compile_status = false;
	}

	// Delete the shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// Delete the shader program
	if (compile_status) {
		glDeleteProgram(ID);
		ID = new_id;
	} else {
		glDeleteProgram(new_id);
	}
}

void HotShader::reset_error_buffers() {
	vert_error_buffer[0] = {'\0'};
	frag_error_buffer[0] = {'\0'};
	link_error_buffer[0] = {'\0'};
}


int main(int argc, char *argv[]) {
	Engine engine;

	Window window("Editor", {800, 600});
	Renderer renderer(window);

	Window window2("Shader Hot Reloader", {800, 600});
	Renderer renderer2(window2, 0, "opengl");

	Clock clock;
	Events events;

	bool rng = true;
	double dt;

	GUI gui(window, renderer);
	GLCanvas canvas({800, 600}, window2, renderer2);

	HotShader shader(gui.vert_buffer, gui.frag_buffer);

	gui.vert_error = shader.vert_error_buffer;
	gui.frag_error = shader.frag_error_buffer;
	gui.link_error = shader.link_error_buffer;

	auto event_handler = [&rng, &gui](SDL_Event &event) {
		if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
			rng = false;
		gui.process_events(event);

		return false;
	};

	Texture tex(renderer2, "image.bmp");

	int start = SDL_GetTicks();
	while (rng) {
		dt = clock.tick(60);

		events.process_events(nullptr, nullptr, nullptr, event_handler);

		gui.update();

		if (gui.run) {
			shader.compile_shader(gui.vert_buffer, gui.frag_buffer);
			if (shader.compile_status) {
				shader.reset_error_buffers();
				gui.error_tab = false;
			} else {
				gui.vert_error = shader.vert_error_buffer;
				gui.frag_error = shader.frag_error_buffer;
				gui.link_error = shader.link_error_buffer;
				gui.error_tab = true;
			}
		}

		renderer.clear(WHITE);
		gui.draw();
		renderer.present();

		canvas.begin();
		renderer2.clear(WHITE);
		tex.render({0, 0, 800, 600});

		shader.set_int("time", (int)SDL_GetTicks() - start);
		canvas.draw(shader);
	}

	return 0;
}
