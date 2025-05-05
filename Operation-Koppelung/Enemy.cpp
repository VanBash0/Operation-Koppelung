#include "Enemy.h"

Enemy::Enemy(std::string name, std::string description, int health, std::vector<std::unique_ptr<Attack>> attacks) : name(name), description(description), health(health), attacks(attacks) {};