#include <fstream>
#include "json.hpp"
#include "ItemManager.h"

const int cache_size = 50;

ItemManager::ItemManager() : items(cache_size) {};

ItemManager::ItemManager() {
	std::ifstream file("items.json");
	nlohmann::json data = nlohmann::json::parse(file);

	for (const auto& itemData : data) {
		int id = itemData["id"];
		std::vector <std::unique_ptr<Item>> attacks;
		items[id] = std::make_unique<Item>(
			itemData["name"].get<std::string>(),
			itemData["description"].get<std::string>(),
			itemData["type"].get<ItemType>(),
			itemData["value"].get<int>());
	}
}

const std::unique_ptr<Item> ItemManager::getItem(int id) {
	return std::make_unique<Item>(*items.at(id));
}