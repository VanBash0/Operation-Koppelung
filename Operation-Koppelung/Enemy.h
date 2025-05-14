#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Attack.h"

class Enemy {
public:
	Enemy(std::string name, std::string description, int health, std::vector<std::shared_ptr<Attack>> attacks);
	std::string getName() const;
	void takeDamage(int damage);
	int getHealth() const;
	std::vector<std::shared_ptr<Attack>> getAttacks() const;
private:
	int health;
	std::string name;
	std::string description;
	std::vector<std::shared_ptr<Attack>> attacks;
};