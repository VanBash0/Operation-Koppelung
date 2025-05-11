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

		for (const auto& roomData : data) {
			if (roomData["id"] == id) {
				rooms.put(id, std::make_shared<Room>(
					roomData["options_id"].get<std::vector<int>>(),
					roomData["enemies_id"].get<std::vector<int>>()));
			}
		}
	}
}