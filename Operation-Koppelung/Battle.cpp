#include <curses.h>
#include "Battle.h"

Battle::Battle(std::vector<int> enemies_id, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<Player> player_, std::shared_ptr<MenuManager> menuManager_) {
    menuManager = menuManager_;
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
    menuManager->setPlayerHealth(player->getHealth());
    menuManager->setPlayerSanity(player->getSanity());
    while (!isBattleOver()) {
        if (isPlayerTurn) {
            playerTurn(spells, spell_names);
            isPlayerTurn = false;
        }
        else {
            enemiesTurn();
            isPlayerTurn = true;
            player_defence = 0;
            menuManager->setPlayerHealth(player->getHealth());
        }
    }
    exit(0);
}

void Battle::playerTurn(const std::vector<std::shared_ptr<Attack>>& spells, const std::vector<std::string>& spell_names) {
    std::vector<std::string> actions = { "Attack", "Magic", "Defend", "Item" };
    int acts_count = 0;
    while (acts_count < 2) {
        int choice = menuManager->run(actions);
        std::vector<std::string> enemy_names;
        for (const auto& enemy : enemies) {
            enemy_names.push_back(enemy->getName() + " HP: " + std::to_string(enemy->getHealth()));
        }
        switch (choice) {
        case 0: {
            int target = menuManager->run(enemy_names);
            if (target != -1) {
                enemies[target]->takeDamage(player->getDamage());
                ++acts_count;
            }
            break;
        }
        case 1: {
            int spell_choice = menuManager->run(spell_names);
            if (spell_choice != -1) {
                int target = menuManager->run(enemy_names);
                if (target != -1) {
					enemies[target]->takeDamage(spells[spell_choice]->damage);
					++acts_count;
				}
                break;
            }
            break;
        }
        case 2:
            player_defence += player->getDefence();
            ++acts_count;
            break;
        case 3:
            ++acts_count;
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
    mvprintw(15, 0, "Player HP: %d", player->getHealth());
    for (size_t i = 0; i < enemies.size(); ++i) {
        mvprintw(11 + i, 0, "%s HP: %d", enemies[i]->getName().c_str(), enemies[i]->getHealth());
    }
    refresh();
    getch();
}