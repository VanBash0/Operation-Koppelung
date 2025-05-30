#pragma once
#include <memory>
#include "Room.h"
#include "LRUCache.h"
#include "OptionManager.h"
#include "ViewManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ItemManager.h"

class RoomManager {
private:
	LRUCache<Room> rooms;
	std::shared_ptr<OptionManager> optionManager;
	std::shared_ptr<ViewManager> viewManager;
	std::shared_ptr<Player> player;
	std::shared_ptr<EnemyManager> enemyManager;
	std::shared_ptr<ItemManager> itemManager;
public:
	RoomManager(std::shared_ptr<OptionManager> optionManager, std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<ItemManager> itemManager);
	void addRoom(int id);
	std::shared_ptr<Room> getRoom(int id);
	void roomProcess(int id);
};