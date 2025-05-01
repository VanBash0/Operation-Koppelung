#include "Enemy.h"

Enemy::Enemy(int id) : id(id) {
	name = "Enemy " + std::to_string(id);
	description = "Description of enemy " + std::to_string(id);
    hp = 20;
    attacks.push_back(std::make_unique<Attack>(1));
    attacks.push_back(std::make_unique<Attack>(2));
    attacks.push_back(std::make_unique<Attack>(3));
}

std::string Enemy::getName() {
	return name;
}

void Enemy::takeDamage(int damage) {
	hp -= damage;
}

int Enemy::getHealth() {
	return hp;
}

Attack& Enemy::getAttack(size_t index) const {
    return *attacks[index];
}

size_t Enemy::getAttackCount() const {
    return attacks.size();
}