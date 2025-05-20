#include <curses.h>
#include "Battle.h"

Battle::Battle(std::vector<int> enemies_id, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<Player> player_, std::shared_ptr<ViewManager> viewManager_) {
    viewManager = viewManager_;
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
    viewManager->setPlayerHealth(player->getHealth());
    viewManager->setPlayerSanity(player->getSanity());
    while (!isBattleOver()) {
        if (isPlayerTurn) {
            playerTurn(spells, spell_names);
            isPlayerTurn = false;
        }
        else {
            enemiesTurn();
            isPlayerTurn = true;
            player_defence = 0;
            viewManager->setPlayerHealth(player->getHealth());
        }
    }
    exit(0);
}

void Battle::playerTurn(const std::vector<std::shared_ptr<Attack>>& spells, const std::vector<std::string>& spell_names) {
    std::vector<std::string> actions = { "Attack", "Magic", "Defend", "Item" };
    int acts_count = 0;
    while (acts_count < 2) {
        int choice = viewManager->run(actions);
        std::vector<std::string> enemy_names;
        for (const auto& enemy : enemies) {
            enemy_names.push_back(enemy->getName() + " HP: " + std::to_string(enemy->getHealth()));
        }
        switch (choice) {
        case 0: {
            int target = viewManager->run(enemy_names);
            if (target != -1) {
                enemies[target]->takeDamage(player->getDamage());
                viewManager->printText("You attack " + enemies[target]->getName() + " with " + player->getWeaponName() + " and deal " + std::to_string(player->getDamage()) + " damage!");
                ++acts_count;
            }
            break;
        }
        case 1: {
            int spell_choice = viewManager->run(spell_names);
            if (spell_choice != -1) {
                int target = viewManager->run(enemy_names);
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
            viewManager->printText((*it)->getName() + " attacks you with " + attacks[attack_idx]->name + " and deals you " + std::to_string(damage) + " damage!");
            viewManager->setPlayerHealth(player->getHealth());
            viewManager->updatePlayerStats();
            ++it;
        }
    }
}

bool Battle::isBattleOver() {
    if (player->getHealth() <= 0) return true;
    return enemies.empty();
}