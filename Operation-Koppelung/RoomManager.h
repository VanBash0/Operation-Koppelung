#pragma once
#include <memory>
#include "Room.h"
#include "LRUCache.h"
#include "OptionManager.h"

class RoomManager {
private:
	LRUCache<Room> rooms;
	std::shared_ptr<OptionManager> optionManager;
public:
	RoomManager(std::shared_ptr<OptionManager> optionManager);
	void addRoom(int id);
	std::shared_ptr<Room> getRoom(int id);
	void roomProcess(int id);
};