#include "Enemy.h"

Enemy::Enemy(std::string name, std::string description, int health, std::vector<const Attack&> attacks) : name(name), description(description), health(health), attacks(attacks) {};