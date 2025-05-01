#pragma once
#include <string>

struct Attack {
public:
	Attack(int id, std::string name, std::string description, int damage, int sanity_cost, bool isDamaging, bool isPhysical);

private:
	int id, damage, sanity_cost;
	std::string name;
	std::string description;
	bool isDamaging, isPhysical;
};