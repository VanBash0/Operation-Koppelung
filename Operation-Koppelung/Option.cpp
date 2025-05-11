#include "Option.h"
#include <curses.h>
#include <iostream>

std::string Option::getDescription() {
	return description;
}

void ExplorationOption::execute() {
    // Заглушка для ExplorationOption
    std::cout << "Выполняется ExplorationOption" << std::endl;
}

void BattleOption::execute() {
    // Заглушка для BattleOption
    std::cout << "Выполняется BattleOption" << std::endl;
}

void GramophoneOption::execute() {
    // Заглушка для GrammophoneOption
    std::cout << "Выполняется GrammophoneOption" << std::endl;
}

void RoomChangeOption::execute() {
    // Заглушка для RoomChangeOption
    std::cout << "Выполняется RoomChangeOption" << std::endl;
}