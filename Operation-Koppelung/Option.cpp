#include "Option.h"
#include <curses.h>
#include <iostream>

void ExplorationOption::execute() {
    // �������� ��� ExplorationOption
    std::cout << "����������� ExplorationOption" << std::endl;
}

void BattleOption::execute() {
    // �������� ��� BattleOption
    std::cout << "����������� BattleOption" << std::endl;
}

void GramophoneOption::execute() {
    // �������� ��� GrammophoneOption
    std::cout << "����������� GrammophoneOption" << std::endl;
}

void RoomChangeOption::execute() {
    // �������� ��� RoomChangeOption
    std::cout << "����������� RoomChangeOption" << std::endl;
}