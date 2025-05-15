#pragma once
#include <memory>
#include "Room.h"
#include "LRUCache.h"
#include "OptionManager.h"
#include "MenuManager.h"

class RoomManager {
private:
	LRUCache<Room> rooms;
	std::shared_ptr<OptionManager> optionManager;
	std::shared_ptr<MenuManager> menuManager;
public:
	RoomManager(std::shared_ptr<OptionManager> optionManager, std::shared_ptr<MenuManager> menuManager);
	void addRoom(int id);
	std::shared_ptr<Room> getRoom(int id);
	void roomProcess(int id);
};