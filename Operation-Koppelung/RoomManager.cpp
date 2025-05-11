#include <fstream>
#include "RoomManager.h"
#include "json.hpp"

const int cache_size = 50;

RoomManager::RoomManager() : rooms(cache_size) {};

std::shared_ptr<Room> RoomManager::getRoom(int id) {
	if (!rooms.get(id)) {
		addRoom(id);
	}
	return rooms.get(id);
}

void RoomManager::addRoom(int id) {
	if (!rooms.contains(id)) {
		std::ifstream file("rooms.json");
		nlohmann::json data = nlohmann::json::parse(file);

		for (const auto& optionData : data) {
			if (optionData["id"] == id) {
				std::string description = optionData["description"].get<std::string>();
				std::vector<std::string> story = optionData["story"].get<std::vector<std::string>>();

				OptionType type = optionData["type"].get<OptionType>();
				std::shared_ptr<Option> option;
				std::vector<int> enemies_id;
			}
		}
	}
}