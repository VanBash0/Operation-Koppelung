#include "Game.h"

Game::Game() {
	attackManager = std::make_shared<AttackManager>();
	std::shared_ptr<OptionManager> optionManager;
	optionManager = std::make_shared<OptionManager>();
	enemyManager = std::make_unique<EnemyManager>(attackManager);
	std::shared_ptr<ItemManager> itemManager;
	itemManager = std::make_shared<ItemManager>();
	roomManager = std::make_unique<RoomManager>(optionManager);
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>(itemManager, attackManager);
}