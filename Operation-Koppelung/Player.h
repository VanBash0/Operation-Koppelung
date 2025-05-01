#pragma once
#include "Item.h"
#include "Attack.h"
#include <memory>
#include <vector>

class Player {
public:
	Player(int hp, int sanity, std::vector<int> items_id, std::vector<int> attacks_id);

private:
	int hp, sanity;
	std::unique_ptr<Item> weapon, armor, amulet;
	std::vector<std::unique_ptr<Item>> inventory;
	std::vector<std::unique_ptr<Attack>> unlocked_spells;
};