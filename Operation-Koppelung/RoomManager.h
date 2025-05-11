#pragma once
#include "Room.h"
#include "LRUCache.h"

class RoomManager {
private:
	LRUCache<Room> rooms;
public:
	RoomManager();
	void addRoom(int id);
	std::shared_ptr<Room> getRoom(int id);
};