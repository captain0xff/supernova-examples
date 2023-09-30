#include <supernova/engine.h>
#include <supernova/constants.h>

#include "json.h"


using namespace std;
using json = nlohmann::json;



int main(int argc, char* argv[]) {

	Engine engine;

	json person;
	person["name"] = "John";
	person["id"] = 132;
	person["balance"] = 20356.87;
	IO f1("data.json", "w");
	f1.write(person.dump());
	f1.close();

	IO f2("data.json");
	json data = json::parse(f2.read());
	string name = data["name"];
	SDL_Log("Name: %s", name.c_str());
	int id = data["id"];
	SDL_Log("ID: %s", name.c_str());
	double balance = data["balance"];
	SDL_Log("Balance: %f", balance);
	f2.close();

	return 0;
}
