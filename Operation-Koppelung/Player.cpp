#include "Player.h"

Player* Player::instance = nullptr;
Player::Player(int hp, int sanity, std::vector<int> items_id, std::vector<int> attacks_id) : 
    hp(hp), 
    sanity(sanity), 
    weapon(items_id.empty() || items_id[0] == -1 ? nullptr : std::make_unique<Item>(items_id[0])), 
    armor(items_id.size() < 2 || items_id[1] == -1 ? nullptr : std::make_unique<Item>(items_id[1])), 
    amulet(items_id.size() < 3 || items_id[2] == -1 ? nullptr : std::make_unique<Item>(items_id[2])) 
{
    for (auto i = 3; i < items_id.size(); ++i) {
        if (items_id[i] != -1) {
            inventory.push_back(std::make_unique<Item>(items_id[i]));
        }
    }

	for (auto i = 0; i < attacks_id.size(); ++i) {
		unlocked_spells.push_back(std::make_unique<Attack>(attacks_id[i]));
	}
}

Player& Player::getInstance() {
    return *instance;
}

void Player::initialize(int hp, int sanity, std::vector<int> items_id, std::vector<int> attacks_id) {
    if (instance) {
        delete instance;
    }
    instance = new Player(hp, sanity, items_id, attacks_id);
}

int Player::getDamage() {
    return (weapon != nullptr) ? weapon->getValue() : 10;
}

int Player::getDefence() {
    return (armor != nullptr) ? armor->getValue() : 10;
}

int Player::getHealth() {
	return hp;
}

void Player::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) {
        hp = 0;
    }
}

Attack& Player::getSpell(size_t index) const {
    return *unlocked_spells[index];
}

size_t Player::getSpellCount() const {
    return unlocked_spells.size();
}