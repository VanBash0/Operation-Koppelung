#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Attack.h"

class Enemy {
public:
	Enemy(std::string name, std::string description, int health, std::vector<const Attack&> attacks);
private:
	int health;
	std::string name, description;
	std::vector<const Attack&> attacks;
};