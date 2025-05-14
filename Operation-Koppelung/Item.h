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
	std::string name;
	std::string description;
	ItemType type;
	int value;
	Item(std::string name, std::string description, ItemType type, int value) : name(name), description(description), type(type), value(value) {};
};