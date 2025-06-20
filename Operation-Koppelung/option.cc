#include "option.h"

#include <curses.h>

#include <iostream>

void ExplorationOption::Execute(ViewManager* view_manager, Player* player,
                                ItemManager* item_manager,
                                EnemyManager* enemy_manager,
                                SaveManager* save_manager) {
  if (!is_picked_) {
    view_manager->PrintTextByLine(story_);
    if (loot_id_ != -1) {
      if (player->InventoryFull()) {
        // Инвентарь полон
        view_manager->PrintText("Your inventory is full!");
      } else {
        // Добавление предмета в инвентарь
        player->AddItem(loot_id_, item_manager);
        view_manager->PrintText("You found " +
                                item_manager->GetItem(loot_id_)->name + "!");
        is_picked_ = true;
        save_manager->SaveOptionPicked(id_);
      }
    } else {
      // Помечаем опцию выбранной при отсутствии предмета
      is_picked_ = true;
      save_manager->SaveOptionPicked(id_);
    }
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
}

void BattleOption::Execute(ViewManager* view_manager, Player* player,
                           ItemManager* item_manager,
                           EnemyManager* enemy_manager,
                           SaveManager* save_manager) {
  if (!is_picked_) {
    view_manager->PrintTextByLine(story_);
    std::unique_ptr<Battle> battle = std::make_unique<Battle>(
        enemies_id_, enemy_manager, player, view_manager);
    if (battle->ExecuteBattle()) {
      is_picked_ = true;
      save_manager->SaveOptionPicked(id_);
    }
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
}

void GramophoneOption::Execute(ViewManager* view_manager, Player* player,
                               ItemManager* item_manager,
                               EnemyManager* enemy_manager,
                               SaveManager* save_manager) {
  if (!is_picked_) {
    is_picked_ = true;
    save_manager->SaveOptionPicked(id_);
    view_manager->PrintTextByLine(story_);
    player->HealSanity(sanity_restore_);
    view_manager->UpdatePlayerStats(player->GetHealth(), player->GetSanity());
    if (player->GetSanity() == 100) {
      view_manager->PrintText("You fully restore your sanity!");
    } else {
      view_manager->PrintText("You heal " + std::to_string(sanity_restore_) +
                              " sanity!");
    }
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
}

void RoomChangeOption::Execute(ViewManager* view_manager, Player* player,
                               ItemManager* item_manager,
                               EnemyManager* enemy_manager,
                               SaveManager* save_manager) {
  if (!is_picked_) {
    is_picked_ = true;
    save_manager->SaveOptionPicked(id_);
    view_manager->PrintTextByLine(story_);
  } else {
    view_manager->PrintTextByLine(after_story_);
  }
  player->SetLocation(room_id_);
}
