#include <fstream>
#include "json.hpp"
#include "Player.h"
Player::Player(std::shared_ptr<ItemManager> itemManager, std::shared_ptr<AttackManager> attackManager) {
	std::ifstream file("player.json");
	nlohmann::json data = nlohmann::json::parse(file);
	health = data[0]["health"].get<int>();
	sanity = data[0]["sanity"].get<int>();
	location = data[0]["location"].get<int>();
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

std::string Player::getWeaponName() const { return weapon->name; }

int Player::getLocation() const { return location; }

void Player::setLocation(const int& loc) { location = loc; }

std::vector<std::shared_ptr<Item>> Player::getItems() const { return inventory; }

std::shared_ptr<Item> Player::getWeapon() const { return weapon; }

std::shared_ptr<Item> Player::getArmor() const { return armor; }

std::shared_ptr<Item> Player::getAmulet() const { return amulet; }

void Player::healHealth(int delta) {
	health = (health + delta > 100) ? 100 : health + delta;
}

void Player::healSanity(int delta) {
	sanity = (sanity + delta > 100) ? 100 : sanity + delta;
}

void Player::loseSanity(int delta) {
	sanity = (sanity - delta < 0) ? 0 : sanity - delta;
}

void Player::update() {
	std::ifstream input_file("player.json");
	nlohmann::json player_data = nlohmann::json::parse(input_file);
	input_file.close();
	player_data[0]["health"] = health;
	player_data[0]["sanity"] = sanity;
	player_data[0]["location"] = location;
	player_data[0]["items_id"].clear();
	for (int i = 0; i < inventory.size(); i++) {
		player_data[0]["items_id"].push_back(inventory[i]->id);
	}
	player_data[0]["weapon_id"] = (weapon == nullptr) ? -1 : weapon->id;
	player_data[0]["armor_id"] = (armor == nullptr) ? -1 : armor->id;
	player_data[0]["amulet_id"] = (amulet == nullptr) ? -1 : amulet->id;
	player_data[0]["spells_id"].clear();
	for (int i = 0; i < spells.size(); i++) {
		player_data[0]["spells_id"].push_back(spells[i]->id);
	}
	std::ofstream output_file("player.json");
	output_file << player_data.dump(4);
	output_file.close();
}