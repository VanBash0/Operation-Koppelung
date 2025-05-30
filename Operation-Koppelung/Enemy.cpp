#include "Enemy.h"

Enemy::Enemy(std::string name, std::string description, int health, std::vector<std::shared_ptr<Attack>> attacks) : name(name), description(description), health(health), attacks(attacks) {};

std::string Enemy::getName() const { return name; }

void Enemy::takeDamage(int damage) {
	health = (health < damage) ? 0 : health - damage;
}

void Enemy::heal(int delta) {
	health += delta;
}

int Enemy::getHealth() const { return health; }

std::vector<std::shared_ptr<Attack>> Enemy::getAttacks() const { return attacks; }