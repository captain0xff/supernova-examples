#include <iostream>

#include <supernova/core.h>
#include <supernova/networking.h>


using namespace std;



string server_discovery(const string keyword) {
	DatagramSocket dscv_socket(2000);
	Packet packet;

	string msg;

	while (true) {
		if ((dscv_socket.get_state() == dscv_socket.READY) && (dscv_socket.recv(packet))) {
			packet >> msg;
			if (msg == keyword) {
				SDL_Log("Recieved keyword successfully!");
				break;
			}
		}
	}

	return SDLNet_GetAddressString(dscv_socket.datagram->addr);
}


void relay(string address) {
	StreamSocket socket(2000, address);

	char buffer[512];

	while (true) {
		if (socket.get_state() == socket.READY) {
			if (socket.read(buffer, 1024) > 0) {
				if (string(buffer) == "quit")
					break;
				cout << address << ":" << socket.port << "-> " << buffer << endl;
			}
		}
	}
}


int main(int argc, char* argv[]) {

	Engine engine;

	const string KEYWORD = "123456";

	string address = server_discovery(KEYWORD);
	// relay(address);

	return 0;
}
