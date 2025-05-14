#include <fstream>
#include "json.hpp"
#include "ItemManager.h"

const int cache_size = 50;

ItemManager::ItemManager() : items(cache_size) {};

std::shared_ptr<Item> ItemManager::getItem(int id) {
	if (!items.get(id)) {
		addItem(id);
	}
	return items.get(id);
}

void ItemManager::addItem(int id) {
	if (!items.contains(id)) {
		std::ifstream file("rooms.json");
		nlohmann::json data = nlohmann::json::parse(file);

		for (const auto& itemData : data) {
			if (itemData["id"] == id) {
				items.put(id, std::make_shared<Item>(
					itemData["name"].get<std::string>(),
					itemData["description"].get<std::string>(),
					itemData["type"].get<ItemType>(),
					itemData["value"].get<int>()));
			}
		}
	}
}