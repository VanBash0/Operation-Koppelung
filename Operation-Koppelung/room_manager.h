#pragma once
#include <memory>

#include "enemy_manager.h"
#include "item_manager.h"
#include "lru_cache.h"
#include "option_manager.h"
#include "player.h"
#include "room.h"
#include "view_manager.h"

class RoomManager {
 private:
  LRUCache<Room> rooms_;
  OptionManager* option_manager_;
  ViewManager* view_manager_;
  Player* player_;
  EnemyManager* enemy_manager_;
  ItemManager* item_manager_;

 public:
  RoomManager(OptionManager* option_manager, ViewManager* view_manager,
              Player* player, EnemyManager* enemy_manager,
              ItemManager* item_manager);
  void AddRoom(int id);
  Room* GetRoom(int id);
  bool RoomProcess(int id);
};
