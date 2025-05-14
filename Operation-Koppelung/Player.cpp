#include <fstream>
#include "json.hpp"
#include "Player.h"
Player::Player(ItemManager* itemManager, AttackManager* attackManager) {
	std::ifstream file("player.json");
	nlohmann::json data = nlohmann::json::parse(file);
	health = data[0]["health"].get<int>();
	sanity = data[0]["sanity"].get<int>();
	for (int i : data[0]["items_id"]) {
		inventory.push_back(itemManager->getItem(i));
	}
	weapon = itemManager->getItem(data[0]["weapon_id"].get<int>());
	armor = itemManager->getItem(data[0]["armor_id"].get<int>());
	amulet = itemManager->getItem(data[0]["amulet_id"].get<int>());
	for (int i : data[0]["spells_id"]) {
		spells.push_back(attackManager->getAttack(i));
	}
}

void Player::update() {
	std::ofstream file("player.json");
	nlohmann::json data = nlohmann::json::parse(file);
	data[0]["health"] = health;
	data[0]["sanity"] = sanity;
	for (int i = 0; i < inventory.size(); i++) {
		data[0]["items_id"][i] = inventory[i]->id;
	}
	data[0]["weapon_id"] = weapon->id;
	data[0]["armor_id"] = armor->id;
	data[0]["amulet_id"] = amulet->id;
	for (int i = 0; i < spells.size(); i++) {
		data[0]["spells_id"][i] = spells[i]->id;
	}
}