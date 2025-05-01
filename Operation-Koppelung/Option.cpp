#include "Option.h"
#include <curses.h>

Option::Option(int id, const std::string& description) : id(id), description(description) {};

void Option::execute() {
	mvprintw(5, 5, "mmmm");
}
	
std::string Option::getDescription() {
	return description;
}
