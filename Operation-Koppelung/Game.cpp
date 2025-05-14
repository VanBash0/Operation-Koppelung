#include "Game.h"

Game::Game() {
	attackManager = std::make_shared<AttackManager>();
	optionManager = std::make_unique<OptionManager>();
	enemyManager = std::make_unique<EnemyManager>(attackManager);
	itemManager = std::make_shared<ItemManager>();
	roomManager = std::make_unique<RoomManager>(optionManager);
	player = std::make_unique<Player>(itemManager, attackManager);
}