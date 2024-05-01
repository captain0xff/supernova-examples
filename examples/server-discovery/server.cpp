#include <iostream>

#include <supernova/core.h>
#include <supernova/networking.h>


using namespace std;



string server_discovery(const string keyword) {
	DatagramSocket dscv_socket(2000);
	Packet packet;

	string msg;

	while (true) {
		if (dscv_socket.recv(packet)) {
			packet >> msg;
			if (msg == keyword) {
				SDL_Log("Recieved keyword successfully!");
				break;
			}
		}
	}

	return dscv_socket.address.get_string();
}


void relay(string addr) {
	// IPaddress client_ip;
	// NetUtils::resolve_host(client_ip, 2000);
	// client_ip.host = ip.host;
	// TCPSocket socket(client_ip);
	StreamSocket socket(2000, addr);

	char buffer[512];

	while (true) {
		if (socket.read(buffer, 1024) > 0) {
			if (string(buffer) == "quit")
				break;
			cout << socket.address.get_string() << ":" << socket.port << " -> " << buffer << endl;
		}
	}
}


int main(int argc, char* argv[]) {

	Engine engine;

	const string KEYWORD = "123456";

	// string addr = server_discovery(KEYWORD);
	relay("127.0.0.1");

	return 0;
}
