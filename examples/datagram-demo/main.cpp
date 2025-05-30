#include <supernova/core.h>
#include <supernova/constants.h>
#include <supernova/networking.h>
#include <SDL3/SDL_main.h>


using namespace std;



int main(int argc, char *argv[]) {
	Engine engine;

	Window window("Datagram Demo", {800, 600});
	Renderer renderer(window);

	Clock clock;
	Events events;

	bool rng = true;
	bool server_ready = false;
	double dt;

	DatagramSocket server(2000), client(0);
	Packet server_packet, client_packet;
	Datagram dgram(2000, "localhost", client_packet);

	Rect server_rect, client_rect;
	server_rect = client_rect = {0, 0, 50, 50};
	Vector pos;

	Mouse mouse;

	while (rng) {
		dt = clock.tick(60);

		rng = events.process_events(nullptr, &mouse);

		client_rect.center(mouse.pos);
		client_rect.clamp_ip({0, 0, 400, 600});

		client_packet << client_rect.center();
		if ((client.get_state() == DatagramSocket::READY) && (dgram.get_state() == Datagram::READY)) {
			client.send(dgram);
		}

		if ((server.get_state() == DatagramSocket::READY) && (server.recv(server_packet))) {
			server_ready = true;
			server_packet >> pos;
			server_rect.center({pos.x + 400, pos.y});
		}

		renderer.clear(WHITE);
		renderer.draw_rect(client_rect, GREEN);
		if (server_ready)
			renderer.draw_rect(server_rect, YELLOW);
		renderer.draw_line({400, 0}, {400, 600}, RED);
		renderer.present();
	}

	return 0;
}

