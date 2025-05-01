#include "Attack.h"

Attack::Attack(int id) : id(id) {
	damage = 10;
	sanity_cost = 0;
	name = "Attack " + std::to_string(id);
	description = "Description of attack " + std::to_string(id);
	isDamaging = true;
	isPhysical = true;
}