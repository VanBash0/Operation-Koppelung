#pragma once
#include "AttackManager.h"
#include "OptionManager.h"
#include "EnemyManager.h"

class Game {
private:
	std::shared_ptr<AttackManager> attackManager;
	std::unique_ptr<OptionManager> optionManager;
	std::unique_ptr<EnemyManager> enemyManager;
public:
	Game();
};