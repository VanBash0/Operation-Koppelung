#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Player.h"
#include "Menu.h"
#include "EnemyManager.h"

class Battle {
private:
    std::vector<std::shared_ptr<Enemy>> enemies;
    Player* player;
    EnemyManager* enemyManager;
    int player_defence = 0;
    bool isPlayerTurn = true;

    void playerTurn(const std::vector<std::shared_ptr<Attack>>& spells, const std::vector<std::string>& spell_names);
    void enemiesTurn();
    bool isBattleOver();
    void showBattleStatus();

public:
    Battle(std::vector<int> enemies_id, EnemyManager* enemyManager, Player* player);
    void start();
};