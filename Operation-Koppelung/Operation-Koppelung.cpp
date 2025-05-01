#include "Room.h"
#include <string>

int main() {
	Room* room = new Room({ 1, 2, 3 }, {});
	room->enterRoom();
	room->getOptions();
	return 0;
}