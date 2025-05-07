#include <fstream>
#include "json.hpp"
#include "Option.h"
#include "OptionManager.h"

const int cache_size = 50;

OptionManager::OptionManager() : options(cache_size) {};

std::shared_ptr<Option> OptionManager::getOption(int id) {
	if (!options.get(id)) {
		addOption(id);
	}
	return options.get(id);
}

void OptionManager::addOption(int id) {
	if (!options.contains(id)) {
		std::ifstream file("options.json");
		nlohmann::json data = nlohmann::json::parse(file);

		for (const auto& optionData : data) {
			if (optionData["id"] == id) {
				options.put(id, std::make_shared<Option>(
					optionData["description"].get<std::string>(),
					optionData["type"].get<OptionType>()));
				break;
			}
		}
	}
}