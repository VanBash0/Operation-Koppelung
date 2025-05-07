#include "Option.h"
#include <curses.h>
Option::Option(std::string description, OptionType type) : description(description), type(type) {};

std::string Option::getDescription() {
	return description;
}