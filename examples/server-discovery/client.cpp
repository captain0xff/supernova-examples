#include <iostream>

#include <supernova/core.h>
#include <supernova/networking.h>


using namespace std;



void server_discovery(const string keyword) {
	int enabled = 1;
	DatagramSocket dscv_socket(0);
	Packet packet;
	Datagram datagram(2000, "239.255.255.250", packet);
	
	packet << keyword;

	while (true) {
		if (dscv_socket.get_state() == dscv_socket.READY) {
			dscv_socket.send(datagram);
			SDL_Log("sent");
			break;
		}
	}
}


void chat() {
	StreamServer server(2000);
	StreamSocket *client;
	string msg;

	while (true) {
		if (server.get_state() == server.READY) {
			client = server.accept_client();
			if (client)
				break;
		}
	}

	SDL_Log("Connection established with server!");

	while (msg != "quit") {
		cout << "Message: ";
		getline(cin, msg);

		client->write(msg);
	}
}


int main(int argc, char* argv[]) {

	Engine engine;

	const string KEYWORD = "123456";

	server_discovery(KEYWORD);
	// chat();

	return 0;
}
