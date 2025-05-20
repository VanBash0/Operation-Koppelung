#pragma once
#include <memory>
#include "Room.h"
#include "LRUCache.h"
#include "OptionManager.h"
#include "MenuManager.h"
#include "Player.h"
#include "EnemyManager.h"

class RoomManager {
private:
	LRUCache<Room> rooms;
	std::shared_ptr<OptionManager> optionManager;
	std::shared_ptr<MenuManager> menuManager;
	std::shared_ptr<Player> player;
	std::shared_ptr<EnemyManager> enemyManager;
public:
	RoomManager(std::shared_ptr<OptionManager> optionManager, std::shared_ptr<MenuManager> menuManager, std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemyManager);
	void addRoom(int id);
	std::shared_ptr<Room> getRoom(int id);
	void roomProcess(int id);
};