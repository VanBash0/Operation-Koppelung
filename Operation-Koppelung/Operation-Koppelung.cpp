#include "Room.h"
#include "Battle.h"
#include <iostream>

int main() {
    std::vector<int> enemies_id = { 1, 2, 3 };
    Player::initialize(100, 100, { 1, 2, 3 }, { 1, 2, 3 });
    int a = Player::getInstance().getDefence();
    Battle battle(enemies_id);
    battle.start();
    return 0;
}