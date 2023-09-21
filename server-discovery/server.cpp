#include <iostream>

#include <supernova/core.h>
#include <supernova/networking.h>


using namespace std;



IPaddress server_discovery(const string keyword) {
	UDPSocket dscv_socket(2000);
	Packet packet(32);

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

	return packet.packet->address;
}


void relay(const IPaddress ip) {
	IPaddress client_ip;
	NetUtils::resolve_host(client_ip, 2000);
	client_ip.host = ip.host;
	TCPSocket socket(client_ip);

	char buffer[512];

	while (true) {
		if (socket.recv(buffer, 1024) > 0) {
			if (string(buffer) == "quit")
				break;
			cout << client_ip.host << ":" << client_ip.port << " -> " << buffer << endl;
		}
	}
}


int main(int argc, char* argv[]) {

	Engine engine;

	const string KEYWORD = "123456";

	IPaddress ip = server_discovery(KEYWORD);
	relay(ip);

	return 0;
}
