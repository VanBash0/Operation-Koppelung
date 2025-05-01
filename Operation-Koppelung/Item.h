#pragma once
#include <string>

enum ItemType {
	WEAPON,
	ARMOR,
	HP_HEALER,
	SANITY_HEALER,
	INSTANT_WEAPON,
};

struct Item {
private:
	int id;
	std::string name;
	std::string description;
	ItemType type;
	int value;

public:
	Item(int id, std::string name, std::string description, ItemType type, int value);
};