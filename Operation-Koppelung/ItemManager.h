#pragma once
#include "LRUCache.h"
#include "Item.h"

class ItemManager {
private:
	std::unordered_map<int, std::unique_ptr<Item>> items;
public:
	ItemManager();
	const std::unique_ptr<Item> getItem(int id);
};