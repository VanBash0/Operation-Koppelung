#pragma once
#include "Item.h"
#include <unordered_map>

class ItemManager {
private:
	std::unordered_map<int, std::unique_ptr<Item>> items;
public:
	ItemManager();
	std::unique_ptr<Item> getItem(int id);
};