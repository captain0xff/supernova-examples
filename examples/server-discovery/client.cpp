#include <iostream>

#include <supernova/core.h>
#include <supernova/print.h>
#include <supernova/networking.h>


using namespace std;



void server_discovery(const string keyword) {
	DatagramSocket dscv_socket(0, "127.0.0.1");
	Address addr("255.255.255.255");
	int status;
	while ((status = dscv_socket.address.get_status()) < 1) {
		if (status == -1)
			print("Error!");
		else
			print(status);
	}

	while ((status = addr.get_status()) < 1) {
		if (status == -1)
			print("Error!");
		else
			print(status);
	}

	Packet packet;
	packet << keyword;
	print("cool");

	dscv_socket.send(2000, dscv_socket.address, packet);
}


void chat() {
	StreamServer server(2000);
	StreamSocket socket;
	string msg;

	while (true) {
		if (server.is_new_connection_available())
			socket = server.accept_client();
	}

	SDL_Log(
		"Connection established with server! Address-> %s:%i",
		socket.address.get_string().c_str(),
		socket.port
	);

	while (msg != "quit") {
		cout << "Message: ";
		getline(cin, msg);

		socket.write(msg);
	}
}


int main(int argc, char* argv[]) {

	Engine engine;

	const string KEYWORD = "123456";

	// server_discovery(KEYWORD);
	chat();

	return 0;
}
