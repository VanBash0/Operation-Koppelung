#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Menu.h"
#include <vector>
#include <memory>

class Battle {
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    int player_defence = 0;
    bool isPlayerTurn = true;

    void playerTurn();
    void enemiesTurn();
    bool isBattleOver();
    void applyEnemyAttacks();
    void showBattleStatus();

public:
    Battle(std::vector<int> enemies_id);
    void start();
};