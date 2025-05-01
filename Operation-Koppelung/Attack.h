#pragma once
#include <string>

struct Attack {
public:
	Attack(int id);
	std::string getName();
	int getDamage();

private:
	int id, damage, sanity_cost;
	std::string name;
	std::string description;
	bool isDamaging, isPhysical;
};