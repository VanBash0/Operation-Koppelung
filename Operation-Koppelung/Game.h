#pragma once
#include "AttackManager.h"
#include "OptionManager.h"
#include "EnemyManager.h"
#include "RoomManager.h"
#include "ItemManager.h"
#include "Player.h"
#include "ViewManager.h"

class Game {
private:
	std::shared_ptr<AttackManager> attackManager;
	std::shared_ptr<OptionManager> optionManager;
	std::shared_ptr<EnemyManager> enemyManager;
	std::unique_ptr<RoomManager> roomManager;
	std::shared_ptr<ItemManager> itemManager;
	std::shared_ptr<Player> player;
	std::shared_ptr<ViewManager> viewManager;
	std::shared_ptr<View> view;
public:
	Game();
};