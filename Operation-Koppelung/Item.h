#pragma once
#include <string>

enum ItemType {
	WEAPON,
	ARMOR,
	AMULET,
	HP_HEALER,
	SANITY_HEALER,
	INSTANT_WEAPON,
};

struct Item {
	int id;
	std::string name;
	std::string description;
	ItemType type;
	int value;
	Item(int id, std::string name, std::string description, ItemType type, int value) : id(id), name(name), description(description), type(type), value(value) {};
};