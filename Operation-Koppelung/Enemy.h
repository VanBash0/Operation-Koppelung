#pragma once
#include "Attack.h"
#include <memory>
#include <vector>

class Enemy {
public:
	Enemy(int id);
	std::string getName();
	void takeDamage(int damage);
	int getHealth();
	Attack& getAttack(size_t index) const;
	size_t getAttackCount() const;
private:
	int id, hp;
	std::string name, description;
	std::vector<std::unique_ptr<Attack>> attacks;
};