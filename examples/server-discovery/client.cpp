#include <iostream>

#include <supernova/core.h>
#include <supernova/networking.h>


using namespace std;



void server_discovery(const string keyword) {
	UDPSocket dscv_socket(0);
	IPaddress srvadd;

	NetUtils::resolve_host(srvadd, 2000, "255.255.255.255");

	Packet packet(32, srvadd);
	packet << keyword;

	dscv_socket.send(packet);
}


void chat() {
	IPaddress ip, *remote_ip;

	NetUtils::resolve_host(ip, 2000);

	TCPSocket client(ip), server;
	string msg;

	while (!client.accept(server));
	remote_ip = server.get_peer_address();
	SDL_Log(
		"Connection established with server! Address-> %s:%i",
		NetUtils::get_formatted_ipv4_host(remote_ip->host).c_str(),
		remote_ip->port
	);

	while (msg != "quit") {
		cout << "Message: ";
		getline(cin, msg);

		server.send(msg);
	}
}


int main(int argc, char* argv[]) {

	Engine engine;

	const string KEYWORD = "123456";

	server_discovery(KEYWORD);
	chat();

	return 0;
}
