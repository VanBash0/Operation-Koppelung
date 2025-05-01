#pragma once
#include <vector>
#include "Option.h"

class Room {
public:
	Room(const std::vector<int>& optionIDs, const std::vector<int>& enemyIDs);

	void enterRoom();
	void getOptions();

private:
	std::vector<int> enemyIDs, optionIDs;
	std::vector<Option*> options;
	bool roomEntered;
};