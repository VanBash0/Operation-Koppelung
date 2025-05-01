#include "Option.h"
#include <curses.h>
Option::Option(int id) : id(id) {
	description = "Option " + std::to_string(id);
}

void Option::execute() {
	mvprintw(5, 5, "mmmm");
}
	
std::string Option::getDescription() {
	return description;
}
