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
private:
	int id;
	std::string name;
	std::string description;
	ItemType type;
	int value;

public:
	Item(int id, std::string name, std::string description, ItemType type, int value);
	Item(int id);

	int getValue();
	std::string getName();
};