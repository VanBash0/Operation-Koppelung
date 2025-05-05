#include <fstream>
#include "json.hpp"
#include "Option.h"

const int CACHE_OPTION_LIMIT = 50;

void OptionManager::addOption(int id) {
	std::ifstream file("attacks.json");
	nlohmann::json data = nlohmann::json::parse(file);

}