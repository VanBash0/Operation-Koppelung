#pragma once
#include "Attack.h"
#include <memory>
#include <vector>

class Enemy {
public:
	Enemy(int id);
private:
	int id, hp;
	std::string name, description;
	std::vector<std::unique_ptr<Attack>> attacks;
};