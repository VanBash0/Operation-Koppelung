#pragma once
#include <unordered_map>
#include <memory>
#include "Enemy.h"
#include "AttackManager.h"

class EnemyManager {
private:
	std::unordered_map<int, std::unique_ptr<Enemy>> enemies;
public:
	EnemyManager(std::shared_ptr<AttackManager> attackManager);
	const std::shared_ptr<Enemy> getEnemy(int id);
};