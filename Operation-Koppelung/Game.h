#pragma once
#include "AttackManager.h"
#include "OptionManager.h"
#include "EnemyManager.h"
#include "RoomManager.h"
#include "ItemManager.h"
#include "Player.h"

class Game {
private:
	std::shared_ptr<AttackManager> attackManager;
	std::unique_ptr<OptionManager> optionManager;
	std::unique_ptr<EnemyManager> enemyManager;
	std::unique_ptr<RoomManager> roomManager;
	std::shared_ptr<ItemManager> itemManager;
	std::unique_ptr<Player> player;
public:
	Game();
};