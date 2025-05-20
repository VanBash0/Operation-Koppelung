#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Player.h"
#include "ViewManager.h"
#include "EnemyManager.h"

class Battle {
private:
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Player> player;
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<ViewManager> viewManager;
    int player_defence = 0;
    bool isPlayerTurn = true;

    void playerTurn(const std::vector<std::shared_ptr<Attack>>& spells, const std::vector<std::string>& spell_names);
    void enemiesTurn();
    bool isBattleOver();

public:
    Battle(std::vector<int> enemies_id, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<Player> player, std::shared_ptr<ViewManager> viewManager);
    void start();
};