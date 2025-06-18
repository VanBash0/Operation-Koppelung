#include "option.h"

#include <curses.h>

#include <iostream>

void ExplorationOption::Execute(ViewManager* view_manager, Player* player,
                                ItemManager* item_manager,
                                EnemyManager* enemy_manager) {
  if (!is_picked_) {
    view_manager->PrintTextByLine(story_);
    if (loot_id_ != -1) {
      if (player->InventoryFull()) {
        view_manager->PrintText("Your inventory is full!");
      } else {
        player->AddItem(loot_id_, item_manager);
        view_manager->PrintText("You found " +
                                item_manager->GetItem(loot_id_)->name + "!");
        is_picked_ = true;
      }
    }
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
}

void BattleOption::Execute(ViewManager* view_manager, Player* player,
                           ItemManager* item_manager,
                           EnemyManager* enemy_manager) {
  if (!is_picked_) {
    view_manager->PrintTextByLine(story_);
    std::unique_ptr<Battle> battle = std::make_unique<Battle>(
        enemies_id_, enemy_manager, player, view_manager);
    if (battle->ExecuteBattle()) {
      is_picked_ = true;
    }
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
}

void GramophoneOption::Execute(ViewManager* view_manager, Player* player,
                               ItemManager* item_manager,
                               EnemyManager* enemy_manager) {
  if (!is_picked_) {
    is_picked_ = true;
    view_manager->PrintTextByLine(story_);
    player->HealSanity(sanity_restore_);
    view_manager->SetPlayerSanity(player->GetSanity());
    view_manager->UpdatePlayerStats();
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
}

void RoomChangeOption::Execute(ViewManager* view_manager, Player* player,
                               ItemManager* item_manager,
                               EnemyManager* enemy_manager) {
  if (!is_picked_) {
    is_picked_ = true;
    view_manager->PrintTextByLine(story_);
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
  player->SetLocation(room_id_);
}
