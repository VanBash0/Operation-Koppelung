#include <fstream>
#include "json.hpp"
#include "ItemManager.h"

ItemManager::ItemManager() {
	std::ifstream file("items.json");
	nlohmann::json data = nlohmann::json::parse(file);

	for (const auto& itemData : data) {
		int id = itemData["id"].get<int>();
		std::vector <std::unique_ptr<Item>> attacks;
		ItemType itemType;
		std::string typeStr = itemData["type"].get<std::string>();
		if (typeStr == "WEAPON") itemType = WEAPON;
		else if (typeStr == "ARMOR") itemType = ARMOR;
		else if (typeStr == "AMULET") itemType = AMULET;
		else if (typeStr == "HP_HEALER") itemType = HP_HEALER;
		else if (typeStr == "SANITY_HEALER") itemType = SANITY_HEALER;
		else if (typeStr == "INSTANT_WEAPON") itemType = INSTANT_WEAPON;
		items[id] = std::make_unique<Item>(
			itemData["id"].get<int>(),
			itemData["name"].get<std::string>(),
			itemData["description"].get<std::string>(),
			itemType,
			itemData["value"].get<int>());
	}
}

std::shared_ptr<Item> ItemManager::getItem(int id) {
	return std::make_shared<Item>(*items.at(id));
}