#include "Attack.h"

Attack::Attack(int id, std::string name, std::string description, int damage, int sanity_cost, bool isDamaging, bool isPhysical) : id(id), name(name), description(description), damage(damage), sanity_cost(sanity_cost), isDamaging(isDamaging), isPhysical(isPhysical) {};