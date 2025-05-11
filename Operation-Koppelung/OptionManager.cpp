#include <fstream>
#include "json.hpp"
#include "Option.h"
#include "OptionManager.h"

const int cache_size = 50;
enum OptionType {
	EXPLORATION,
	BATTLE,
	GRAMOPHONE,
	ROOMCHANGE,
};

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

				OptionType type = optionData["type"].get<OptionType>();
				std::shared_ptr<Option> option;
				std::vector<int> enemies_id;
				switch (type) {
					case EXPLORATION:
						int loot_id = optionData["loot_id"].get<int>();
						option = std::make_shared<ExplorationOption>(id, description, story, loot_id);
						break;
					case BATTLE:
						enemies_id = optionData["enemies_id"].get<std::vector<int>>();
						option = std::make_shared<BattleOption>(id, description, story, enemies_id);
						break;
					case GRAMOPHONE:
						int sanity_restore = optionData["sanity_restore"].get<int>();
						option = std::make_shared<GramophoneOption>(id, description, story, sanity_restore);
						break;
					case ROOMCHANGE:
						int room_id = optionData["room_id"].get<int>();
						option = std::make_shared<RoomChangeOption>(id, description, story, room_id);
						break;
				}
				options.put(id, option);
				break;
			}
		}
	}
}