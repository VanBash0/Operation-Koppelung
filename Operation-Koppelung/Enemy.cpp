#include "Enemy.h"

Enemy::Enemy(int id) : id(id) {
	name = "Enemy " + std::to_string(id);
	description = "Description of enemy " + std::to_string(id);
    hp = 100;
    attacks.push_back(std::make_unique<Attack>(1));
    attacks.push_back(std::make_unique<Attack>(2));
    attacks.push_back(std::make_unique<Attack>(3));
}