#include <supernova/engine.h>
#include <supernova/constants.h>

#include <iostream>

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
	cout << data["name"] << endl;
	cout << data["id"] << endl;
	cout << data["balance"] << endl;
	f2.close();


	return 0;
}
