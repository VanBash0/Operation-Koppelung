#include "Item.h"

Item::Item(int id, std::string name, std::string description, ItemType type, int value) : id(id), name(name), description(description), type(type), value(value) {}

Item::Item(int id) : id(id) {
	name = "Item " + std::to_string(id);
	description = "Description of item " + std::to_string(id);
	type = ItemType::HP_HEALER;
	value = 0;
}