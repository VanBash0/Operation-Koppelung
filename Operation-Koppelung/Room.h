#pragma once
#include <vector>
#include <memory>

struct Room {
	Room(const std::vector<int>& options_id, const std::vector<int>& enemies_id, const bool& room_entered) : options_id(options_id), enemies_id(enemies_id), room_entered(room_entered) {};
	std::vector<int> options_id;
	std::vector<int> enemies_id;
	bool room_entered;
};