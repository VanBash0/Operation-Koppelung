#include <fstream>
#include "json.hpp"
#include "Player.h"
Player::Player(std::shared_ptr<ItemManager> itemManager, std::shared_ptr<AttackManager> attackManager) {
	std::ifstream file("player.json");
	nlohmann::json data = nlohmann::json::parse(file);
	health = data[0]["health"].get<int>();
	sanity = data[0]["sanity"].get<int>();
	for (int i : data[0]["items_id"]) {
		inventory.push_back(itemManager->getItem(i));
	}
	int weapon_id = data[0]["weapon_id"].get<int>();
	weapon = (weapon_id == -1) ? nullptr : itemManager->getItem(weapon_id);
	int armor_id = data[0]["armor_id"].get<int>();
	armor = (armor_id == -1) ? nullptr : itemManager->getItem(armor_id);
	int amulet_id = data[0]["amulet_id"].get<int>();
	amulet = (amulet_id == -1) ? nullptr : itemManager->getItem(amulet_id);
	for (int i : data[0]["spells_id"]) {
		spells.push_back(attackManager->getAttack(i));
	}
}

void Player::takeDamage(int damage) {
	health = (health < damage) ? 0 : health - damage;
}

int Player::getDamage() const { return weapon->value; }

std::vector<std::shared_ptr<Attack>> Player::getSpells() const { return spells; }

int Player::getDefence() const { return armor->value; }

int Player::getHealth() const { return health; }

int Player::getSanity() const { return sanity; }

//void Player::update() {
//	std::ofstream file("player.json");
//	nlohmann::json data = nlohmann::json::parse(file);
//	data[0]["health"] = health;
//	data[0]["sanity"] = sanity;
//	for (int i = 0; i < inventory.size(); i++) {
//		data[0]["items_id"][i] = inventory[i]->id;
//	}
//	data[0]["weapon_id"] = weapon->id;
//	data[0]["armor_id"] = armor->id;
//	data[0]["amulet_id"] = amulet->id;
//	for (int i = 0; i < spells.size(); i++) {
//		data[0]["spells_id"][i] = spells[i]->id;
//	}
//}