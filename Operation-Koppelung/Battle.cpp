#include "Battle.h"
#include <curses.h>

Battle::Battle(std::vector<int> enemies_id) {
    for (int id : enemies_id) {
        enemies.push_back(std::make_unique<Enemy>(id));
    }
}

void Battle::start() {
    while (!isBattleOver()) {
        showBattleStatus();
        if (isPlayerTurn) {
            playerTurn();
            isPlayerTurn = false;
        }
        else {
            enemiesTurn();
            isPlayerTurn = true;
            player_defence = 0;
        }
    }
}

void Battle::playerTurn() {
    std::vector<std::string> actions = { "Attack", "Magic", "Defend", "Item" };
    for (int i = 0; i < 2; ++i) {
        Menu actionMenu(actions);
        int choice = actionMenu.run();
        std::vector<std::string> enemy_names;
        for (const auto& enemy : enemies) {
            enemy_names.push_back(enemy->getName());
        }
        switch (choice) {
        case 0: { // Attack
            Menu enemy_menu(enemy_names);
            int target = enemy_menu.run();
            enemies[target]->takeDamage(Player::getInstance().getDamage());
            break;
        }
        case 1: { // Magic
            std::vector<std::string> spell_names;
            for (int index = 0; index < Player::getInstance().getSpellCount(); ++index) {
                spell_names.push_back(Player::getInstance().getSpell(index).getName());
            }
            Menu spell_menu(spell_names);
            int spellChoice = spell_menu.run();
            Menu enemyMenu(enemy_names);
            int target = enemyMenu.run();
            enemies[target]->takeDamage(Player::getInstance().getSpell(spellChoice).getDamage());
            break;
        }
        case 2: // Defend
            player_defence += Player::getInstance().getDefence();
            break;
        case 3: // Item (заглушка)
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
            if ((*it)->getAttackCount() > 0) {
                int attackIndex = rand() % (*it)->getAttackCount();
                Attack& attack = (*it)->getAttack(attackIndex);
                int damage = std::max(0, attack.getDamage() - player_defence);
                player_defence = std::max(0, player_defence - attack.getDamage());
                Player::getInstance().takeDamage(damage);
            }
            ++it;
        }
    }
}

bool Battle::isBattleOver() {
    if (Player::getInstance().getHealth() <= 0) return true;
    return enemies.empty();
}

void Battle::showBattleStatus() {
    clear();
    mvprintw(0, 0, "Player HP: %d", Player::getInstance().getHealth());
    for (size_t i = 0; i < enemies.size(); ++i) {
        mvprintw(1 + i, 0, "%s HP: %d", enemies[i]->getName().c_str(), enemies[i]->getHealth());
    }
    refresh();
    getch();
}