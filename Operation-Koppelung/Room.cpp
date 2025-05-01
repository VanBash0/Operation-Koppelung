#include "Room.h"
#include "Menu.h"

Room::Room(const std::vector<int>& optionIDs, const std::vector<int>& enemyIDs) : optionIDs(optionIDs), enemyIDs(enemyIDs), roomEntered(false) {};

void Room::enterRoom() {
	roomEntered = true;
	if (!enemyIDs.empty()) {
		// инициализация битвы на входе в комнату!
	}
	for (int id : optionIDs) {
		options.push_back(new Option(id, "Option " + std::to_string(id)));
	}
}

void Room::getOptions() {
	std::vector<std::string> options_desc;
	for (Option* option : options) {
		options_desc.push_back(option->getDescription());
	}
	Menu* menu = new Menu(options_desc);
	while (true) {
		int choice = menu->run();
		options[choice]->execute();
		menu->waitUntilHit();
	}
}