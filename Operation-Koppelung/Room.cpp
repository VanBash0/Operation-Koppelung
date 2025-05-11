#include "Room.h"
#include "Menu.h"

Room::Room(const std::vector<int>& options_id, const std::vector<int>& enemies_id) : options_id(options_id), enemies_id(enemies_id), roomEntered(roomEntered) {};

void Room::enterRoom() {
	roomEntered = true;
	if (!enemies_id.empty()) {
		// инициализация битвы на входе в комнату
	}
	for (int id : options_id) {
		options.push_back(std::make_unique<Option>(id));
	}
}
void Room::getOptions() {
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