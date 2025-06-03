#include <utility>
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
            player_defence = player->getDefence();
            playerTurn(spells, spell_names);
            isPlayerTurn = false;
        }
        else {
            enemiesTurn();
            isPlayerTurn = true;
            viewManager->setPlayerHealth(player->getHealth());
        }
    }
    if (player->getHealth() > 0) {
        viewManager->printText("You won!");
    }
    else {
        exit(0);
    }
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
        std::vector<std::string> item_names;
		for (const auto& item : player->getItems()) {
			item_names.push_back(item->name);
		}
        if (choice == 0) {
            int target = viewManager->run(enemy_names);
            if (target != -1) {
                enemies[target]->takeDamage(player->getDamage());
                viewManager->printText("You attack " + enemies[target]->getName() + " with " + player->getWeaponName() + " and deal " + std::to_string(player->getDamage()) + " damage!");
                ++acts_count;
            }
        }
        else if (choice == 1) {
            while (true) {
                int spell_choice = viewManager->run(spell_names);
                if (spell_choice != -1) {
                    if (player->getSanity() >= spells[spell_choice]->sanity_cost) {
                        if (spells[spell_choice]->is_damaging) {
                            int target = viewManager->run(enemy_names);
                            if (target != -1) {
                                enemies[target]->takeDamage(spells[spell_choice]->damage);
                                viewManager->printText("You attack " + enemies[target]->getName() + " with " + spells[spell_choice]->name + " and deal " + std::to_string(spells[spell_choice]->damage) + " damage!;You lose " + std::to_string(spells[spell_choice]->sanity_cost) + " sanity!");
                                player->loseSanity(spells[spell_choice]->sanity_cost);
                                viewManager->setPlayerSanity(player->getSanity());
                                viewManager->updatePlayerStats();
                                ++acts_count;
                            }
                            break;
                        }
                        else {
                            player->healHealth(spells[spell_choice]->damage);
							viewManager->printText("You heal " + std::to_string(spells[spell_choice]->damage) + " health with " + spells[spell_choice]->name + "!;You lose " + std::to_string(spells[spell_choice]->sanity_cost) + " sanity!");
							player->loseSanity(spells[spell_choice]->sanity_cost);
							viewManager->setPlayerSanity(player->getSanity());
                            viewManager->setPlayerHealth(player->getHealth());
							viewManager->updatePlayerStats();
							++acts_count;
							break;
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
        else if (choice == 2) {
            int delta = player->getHealth() / 10;
            player_defence += delta;
            viewManager->printText("You make a defensive pose. Your defence rises by " + std::to_string(delta) + "!");
            ++acts_count;
        }   
        else if (choice == 3 && !player->getItems().empty()) {
			int item_choice = viewManager->run(item_names);
            if (item_choice != -1) {
                std::shared_ptr<Item> item = player->getItems()[item_choice];
                switch (item->type) {
                case WEAPON:
                    viewManager->printText("You equip " + item->name + "!");
                    player->getWeapon().swap(item);
                    break;
                case ARMOR:
					viewManager->printText("You equip " + item->name + "!");
					player->getArmor().swap(item);
					break;
                case HP_HEALER:
                    player->healHealth(item->value);
                    if (player->getHealth() == 100) {
                        viewManager->printText("You use " + item->name + "and fully restore your health!");
                    }
                    else {
						viewManager->printText("You use " + item->name + "and heal" + std::to_string(item->value) + " health!");
                    }
                    player->removeItem(item->id);
                    viewManager->setPlayerHealth(player->getHealth());
                    viewManager->updatePlayerStats();
					break;
				case SANITY_HEALER:
                    player->healSanity(item->value);
                    if (player->getSanity() == 100) {
                        viewManager->printText("You use " + item->name + "and fully restore your sanity!");
                    }
                    else {
                        viewManager->printText("You use " + item->name + "and heal" + std::to_string(item->value) + " sanity!");
                    }
                    player->removeItem(item->id);
                    viewManager->setPlayerSanity(player->getSanity());
                    viewManager->updatePlayerStats();
                    break;
                case INSTANT_WEAPON:
                    for (auto it = enemies.begin(); it != enemies.end(); ) {
                        (*it)->takeDamage(item->value);
                        ++it;
                    }
					viewManager->printText("You use " + item->name + "and deal " + std::to_string(item->value) + " damage to all enemies!");
                    player->removeItem(item->id);
                    break;
				}
            }
            ++acts_count;
        }

        for (auto it = enemies.begin(); it != enemies.end(); ) {
			if ((*it)->getHealth() <= 0) {
				viewManager->printText("You kill " + (*it)->getName() + "!");
                it = enemies.erase(it);
			}
			else {
				++it;
			}
		}

        if (isBattleOver()) {
            break;
        }
    }
}

void Battle::enemiesTurn() {
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        std::vector<std::shared_ptr<Attack>> attacks = (*it)->getAttacks();
        int attack_idx = rand() % attacks.size();
        int damage = std::max(0, attacks[attack_idx]->damage - player_defence);
        player_defence = std::max(0, player_defence - attacks[attack_idx]->damage);
        if (attacks[attack_idx]->is_damaging) {
            switch (attacks[attack_idx]->is_physical) {
            case true:
                player->takeDamage(damage);
                viewManager->printText((*it)->getName() + " attacks you with " + attacks[attack_idx]->name + " and deals you " + std::to_string(damage) + " damage!");
                break;
            case false:
                player->loseSanity(damage);
                viewManager->printText((*it)->getName() + " attacks you with " + attacks[attack_idx]->name + " and deals you " + std::to_string(damage) + " sanity damage!");
                break;
            }
        }
        else {
            (*it)->heal(attacks[attack_idx]->damage);
            viewManager->printText((*it)->getName() + " heals themselves with " + attacks[attack_idx]->name + " and restores " + std::to_string(attacks[attack_idx]->damage) + " health!");
        }
        viewManager->setPlayerHealth(player->getHealth());
        viewManager->updatePlayerStats();
        ++it;
    }
}

bool Battle::isBattleOver() {
    if (player->getHealth() <= 0) return true;
    return enemies.empty();
}