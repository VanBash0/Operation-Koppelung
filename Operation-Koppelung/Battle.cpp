#include <curses.h>
#include "Battle.h"

Battle::Battle(std::vector<int> enemies_id, EnemyManager* enemyManager, Player* player_) {
    player = player_;
    for (int id : enemies_id) {
        enemies.push_back(enemyManager->getEnemy(id));
    }
}

void Battle::start() {
    std::vector<std::shared_ptr<Attack>> spells = player->getSpells();
    std::vector<std::string> spell_names;
    for (const auto& spell : spells) {
		spell_names.push_back(spell->name);
    }
    while (!isBattleOver()) {
        showBattleStatus();
        if (isPlayerTurn) {
            playerTurn(spells, spell_names);
            isPlayerTurn = false;
        }
        else {
            enemiesTurn();
            isPlayerTurn = true;
            player_defence = 0;
        }
    }
}

void Battle::playerTurn(const std::vector<std::shared_ptr<Attack>>& spells, const std::vector<std::string>& spell_names) {
    std::vector<std::string> actions = { "Attack", "Magic", "Defend", "Item" };
    int acts_count = 0;
    while (acts_count < 2) {
        std::unique_ptr<Menu> actionMenu = std::make_unique<Menu>(actions);
        int choice = actionMenu->run();
        std::vector<std::string> enemy_names;
        for (const auto& enemy : enemies) {
            enemy_names.push_back(enemy->getName());
        }
        switch (choice) {
        case 0: {
            std::unique_ptr<Menu> enemyMenu = std::make_unique<Menu>(actions);
            int target = enemyMenu->run();
            if (target != -1) {
                enemies[target]->takeDamage(player->getDamage());
                ++acts_count;
            }
            break;
        }
        case 1: {
            std::unique_ptr<Menu> spellMenu = std::make_unique<Menu>(spell_names);
            int spellChoice = spellMenu->run();
            std::unique_ptr<Menu> enemyMenu = std::make_unique<Menu>(enemy_names);
            int target = enemyMenu->run();
            enemies[target]->takeDamage(spells[spellChoice]->damage);
            break;
        }
        case 2:
            player_defence += player->getDefence();
            break;
        case 3:
            mvprintw(10, 0, "Items not implemented yet!");
            break;
        }
    }
}

void Battle::enemiesTurn() {
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->getHealth() <= 0) {
            it = enemies.erase(it);
        }
        else {
            std::vector<std::shared_ptr<Attack>> attacks = (*it)->getAttacks();
            int attack_idx = rand() % attacks.size();
            int damage = std::max(0, attacks[attack_idx]->damage - player_defence);
            player_defence = std::max(0, player_defence - attacks[attack_idx]->damage);
            player->takeDamage(damage);
            ++it;
        }
    }
}

bool Battle::isBattleOver() {
    if (player->getHealth() <= 0) return true;
    return enemies.empty();
}

void Battle::showBattleStatus() {
    clear();
    mvprintw(0, 0, "Player HP: %d", player->getHealth());
    for (size_t i = 0; i < enemies.size(); ++i) {
        mvprintw(1 + i, 0, "%s HP: %d", enemies[i]->getName().c_str(), enemies[i]->getHealth());
    }
    refresh();
    getch();
}