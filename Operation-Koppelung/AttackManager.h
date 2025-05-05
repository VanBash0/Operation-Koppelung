#pragma once
#include <unordered_map>
#include <memory>
#include "Attack.h"

class AttackManager {
private:
	std::unordered_map<int, std::unique_ptr<Attack>> attacks;
public:
	AttackManager();
	const std::unique_ptr<Attack> getAttack(int id) const;
};