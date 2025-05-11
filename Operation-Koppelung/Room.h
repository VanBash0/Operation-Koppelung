#pragma once
#include <vector>
#include <memory>
#include "Option.h"

class Room {
public:
	Room(const std::vector<int>& options_id, const std::vector<int>& enemies_id);

	void enterRoom();
	void getOptions();

private:
	std::vector<int> enemies_id, options_id;
	std::vector<std::unique_ptr<Option>> options;
	bool roomEntered;
};