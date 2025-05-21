#include <fstream>
#include "json.hpp"
#include "Option.h"
#include "OptionManager.h"

const size_t cache_size = 50;

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
				std::string description = optionData["description"].get<std::string>();
				std::vector<std::string> story = optionData["story"].get<std::vector<std::string>>();
				std::string typeStr = optionData["type"].get<std::string>();
				std::shared_ptr<Option> option;
				std::vector<int> enemies_id;
				if (typeStr == "EXPLORATION") {
					int loot_id = optionData["loot_id"].get<int>();
					option = std::make_shared<ExplorationOption>(description, story, loot_id);
				}
				else if (typeStr == "BATTLE") {
					enemies_id = optionData["enemies_id"].get<std::vector<int>>();
					option = std::make_shared<BattleOption>(description, story, enemies_id);
				}
				else if (typeStr == "GRAMOPHONE") {
					int sanity_restore = optionData["sanity_restore"].get<int>();
					option = std::make_shared<GramophoneOption>(description, story, sanity_restore);
				}
				else if (typeStr == "ROOMCHANGE") {
					int room_id = optionData["room_id"].get<int>();
					option = std::make_shared<RoomChangeOption>(description, story, room_id);
				}
				options.put(id, option);
				break;
			}
		}
	}
}