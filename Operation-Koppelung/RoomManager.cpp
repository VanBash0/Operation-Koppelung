#include <fstream>
#include "json.hpp"
#include "RoomManager.h"
#include "Menu.h"

const int cache_size = 50;

RoomManager::RoomManager(std::shared_ptr<OptionManager> optionManager) : rooms(cache_size), optionManager(optionManager) {};

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
					roomData["enemies_id"].get<std::vector<int>>(),
					roomData["room_entered"].get<bool>()));
			}
		}
	}
}

void RoomManager::roomProcess(int id) {
	std::shared_ptr<Room> room = getRoom(id);
	room->room_entered = true;
	if (!room->enemies_id.empty()) {
		// инициализация битвы на входе в комнату!!!
	}
	std::vector<std::shared_ptr<Option>> options;
	for (int i : room->options_id) {
		options.push_back(optionManager->getOption(id));
	}
	std::vector<std::string> options_desc;
	for (const auto& option : options) {
		options_desc.push_back(option->getDescription());
	}
	std::unique_ptr<Menu> menu = std::make_unique<Menu>(options_desc);
	while (true) {
		int choice = menu->run();
		if (choice != -1) {
			options[choice]->execute();
		}
		else {
			break;
		}
		menu->waitUntilHit();
	}
}