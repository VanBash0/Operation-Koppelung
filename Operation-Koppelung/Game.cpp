#include "Game.h"

Game::Game() {
	attackManager = std::make_shared<AttackManager>();
	optionManager = std::make_unique<OptionManager>();
	enemyManager = std::make_unique<EnemyManager>(attackManager);
}