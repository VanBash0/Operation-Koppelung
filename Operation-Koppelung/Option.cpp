#include "Option.h"

Option::Option(int id, const std::string& description) : id(id), description(description) {};

void Option::execute() {}

std::string Option::getDescription() {
	return description;
}
