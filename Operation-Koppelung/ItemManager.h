#pragma once
#include "LRUCache.h"
#include "Item.h"

class ItemManager {
private:
	LRUCache<Item> items;
public:
	ItemManager();
	void addItem(int id);
	std::shared_ptr<Item> getItem(int id);
};