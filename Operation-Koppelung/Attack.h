#pragma once

struct Attack {
public:
	Attack(int damage, int sanity_cost, std::string name, std::string description, bool is_damaging, bool is_physical) : damage(damage), sanity_cost(sanity_cost), name(name), description(description), is_damaging(is_damaging), is_physical(is_physical) {};
	int damage;
	int sanity_cost;
	std::string name;
	std::string description;
	bool is_damaging;
	bool is_physical;
};