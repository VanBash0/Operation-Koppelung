#include "room_manager.h"

#include <fstream>

#include "battle.h"
#include "json.hpp"

namespace {
constexpr size_t kCacheSize = 10;
}

RoomManager::RoomManager(OptionManager* option_manager,
                         ViewManager* view_manager, Player* player,
                         EnemyManager* enemy_manager, ItemManager* item_manager,
                         SaveManager* save_manager)
    : option_manager_(option_manager),
      view_manager_(view_manager),
      player_(player),
      enemy_manager_(enemy_manager),
      item_manager_(item_manager),
      save_manager_(save_manager),
      rooms_(kCacheSize) {}

Room* RoomManager::GetRoom(int id) {
  if (!rooms_.Get(id)) {
    AddRoom(id);
  }
  return rooms_.Get(id);
}

void RoomManager::AddRoom(int id) {
  if (!rooms_.Contains(id)) {
    std::ifstream file("rooms.json");
    nlohmann::json data = nlohmann::json::parse(file);

    for (const auto& room_data : data) {
      if (room_data["id"] == id) {
        rooms_.Put(id, std::make_unique<Room>(
                           room_data["options_id"].get<std::vector<int>>(),
                           room_data["enemies_id"].get<std::vector<int>>(),
                           room_data["room_entered"].get<bool>()));
      }
    }
  }
}

bool RoomManager::RoomProcess(int id) {
  Room* room = GetRoom(id);
  view_manager_->UpdatePlayerStats(player_->GetHealth(), player_->GetSanity());

  if (!room->enemies_id_.empty() && !room->room_entered_) {
    std::unique_ptr<Battle> battle = std::make_unique<Battle>(
        room->enemies_id_, enemy_manager_, player_, view_manager_);
    if (battle->ExecuteBattle()) {
      room->room_entered_ = true;
      save_manager_->SaveRoomEntered(id);
      save_manager_->SavePlayer(player_);
    } else {
      save_manager_->SavePlayer(player_);
      return true;
    }
  }

  if (!room->room_entered_) {
    room->room_entered_ = true;
    save_manager_->SaveRoomEntered(id);
  }

  std::vector<Option*> options;
  for (int i : room->options_id_) {
    options.push_back(option_manager_->GetOption(i));
  }
  std::vector<std::string> options_desc;
  for (auto option : options) {
    options_desc.push_back(option->GetDescription());
  }
  while (player_->GetLocation() == id) {
    int choice = view_manager_->Run(options_desc);

    // Выход в главное меню
    if (choice == -2) {
      return false;
    }

    // Открыть инвентарь
    if (choice == -3) {
      if (player_->GetItems().empty()) {
        view_manager_->PrintText("Your inventory is empty!");
        break;
      }
      std::vector<std::string> names;
      std::vector<std::string> descriptions;
      for (auto& item : player_->GetItems()) {
        names.push_back(item->name);
        descriptions.push_back(item->description);
      }
      while (true) {
        int choice = view_manager_->Run(names);
        switch (choice) {
          case -2:
            return false;
          case -1:
          case -3:
            return true;
          default:
            view_manager_->PrintText(descriptions[choice]);
            break;
        }
      }
      break;
    }

    // Выполнить опцию
    if (choice != -1) {
      options[choice]->Execute(view_manager_, player_, item_manager_,
                               enemy_manager_, save_manager_);
      save_manager_->SavePlayer(player_);
    }
  }
  return true;
}
