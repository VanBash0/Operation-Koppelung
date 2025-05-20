#include "Game.h"
#include <iostream>

int main() {
	std::shared_ptr<AttackManager> attackManager = std::make_shared<AttackManager>();
	std::shared_ptr<OptionManager> optionManager = std::make_shared<OptionManager>();
	std::shared_ptr<EnemyManager> enemyManager = std::make_shared<EnemyManager>(attackManager);
	std::shared_ptr<ItemManager> itemManager = std::make_shared<ItemManager>();
	std::shared_ptr<View> view = std::make_shared<View>();
	std::shared_ptr<ViewManager> viewManager = std::make_shared<ViewManager>(view);
	std::shared_ptr<Player> player = std::make_shared<Player>(itemManager, attackManager);
	std::unique_ptr<RoomManager> roomManager = std::make_unique<RoomManager>(optionManager, viewManager, player, enemyManager);

	//std::vector<std::string> actions = { "Attack", "Magic", "Defend", "Item" };
	//int choice = viewManager->run(actions);
	roomManager->roomProcess(1);
}