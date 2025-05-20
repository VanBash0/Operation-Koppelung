#include "Game.h"

Game::Game() {
	attackManager = std::make_shared<AttackManager>();
	optionManager = std::make_shared<OptionManager>();
	enemyManager = std::make_shared<EnemyManager>(attackManager);
	itemManager = std::make_shared<ItemManager>();
	view = std::make_shared<View>();
	menuManager = std::make_shared<MenuManager>(view);
	player = std::make_shared<Player>(itemManager, attackManager);
	roomManager = std::make_unique<RoomManager>(optionManager, menuManager, player, enemyManager);
}