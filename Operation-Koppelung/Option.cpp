#include "Option.h"
#include <curses.h>
Option::Option(std::string description) : description(description) {};

void Option::execute() {
	mvprintw(5, 5, "placeholder");
}

std::string Option::getDescription() {
	return description;
}