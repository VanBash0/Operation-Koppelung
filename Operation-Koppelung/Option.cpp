#include "Option.h"
#include <curses.h>
#include <iostream>

void ExplorationOption::execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) {
    if (!isPicked) {
        viewManager->printTextByLine(story);
        if (player->inventoryFull()) {
            viewManager->printText("Your inventory is full!");
        }
		else {
			player->addItem(loot_id, itemManager);
            viewManager->printText("You found " + itemManager->getItem(loot_id)->name + "!");
            isPicked = true;
		}
    }
    else {
        viewManager->printTextByLine(after_story);
    }
}

void BattleOption::execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) {
    if (!isPicked) {
        isPicked = true;
		viewManager->printTextByLine(story);
        std::unique_ptr<Battle> battle = std::make_unique<Battle>(enemies_id, enemyManager, player, viewManager);
        battle->start();
    }
    else {
		viewManager->printTextByLine(after_story);
    }
}

void GramophoneOption::execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) {
    if (!isPicked) {
        isPicked = true;
        viewManager->printTextByLine(story);
        player->healSanity(sanity_restore);
    }
    else {
        viewManager->printTextByLine(after_story);
    }
}

void RoomChangeOption::execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) {
    if (!isPicked) {
        isPicked = true;
        viewManager->printTextByLine(story);
    }
    else {
        viewManager->printTextByLine(after_story);
    }
    player->setLocation(room_id);
}