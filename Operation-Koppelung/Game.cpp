#include "Game.h"

Game::Game() {
	attackManager = std::make_shared<AttackManager>();
	optionManager = std::make_shared<OptionManager>();
	enemyManager = std::make_shared<EnemyManager>(attackManager);
	itemManager = std::make_shared<ItemManager>();
	view = std::make_shared<View>();
	viewManager = std::make_shared<ViewManager>(view);
	player = std::make_shared<Player>(itemManager, attackManager);
	roomManager = std::make_unique<RoomManager>(optionManager, viewManager, player, enemyManager, itemManager);
}

void Game::play() {
	while (true) {
		roomManager->roomProcess(player->getLocation());
	}
}