#include "room_manager.h"

#include <fstream>

#include "battle.h"
#include "json.hpp"

static const size_t kCacheSize = 50;

RoomManager::RoomManager(OptionManager* option_manager,
                         ViewManager* view_manager, Player* player,
                         EnemyManager* enemy_manager, ItemManager* item_manager)
    : option_manager_(option_manager),
      view_manager_(view_manager),
      player_(player),
      enemy_manager_(enemy_manager),
      item_manager_(item_manager),
      rooms_(kCacheSize) {};
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

void RoomManager::RoomProcess(int id) {
  Room* room = GetRoom(id);
  if (!room->enemies_id_.empty() && room->room_entered_ == false) {
    std::unique_ptr<Battle> battle = std::make_unique<Battle>(
        room->enemies_id_, enemy_manager_, player_, view_manager_);
    if (battle->ExecuteBattle()) {
      room->room_entered_ = true;
    } else {
      return;
    }
  }

  std::vector<Option*> options;
  for (int i : room->options_id_) {
    options.push_back(option_manager_->GetOption(i));
  }
  std::vector<std::string> options_desc;
  for (auto option : options) {
    if (option == nullptr) {
      options_desc.push_back("ERROR");
    } else {
      options_desc.push_back(option->GetDescription());
    }
  }
  while (true) {
    if (player_->GetLocation() == id) {
      int choice = view_manager_->Run(options_desc);
      if (choice != -1) {
        options[choice]->Execute(view_manager_, player_, item_manager_,
                                 enemy_manager_);
      } else {
        break;
      }
    } else {
      break;
    }
  }
}
