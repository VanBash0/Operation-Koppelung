#ifndef ROOM_MANAGER_H_
#define ROOM_MANAGER_H_

#include <memory>

#include "enemy_manager.h"
#include "item_manager.h"
#include "lru_cache.h"
#include "option_manager.h"
#include "player.h"
#include "room.h"
#include "save_manager.h"
#include "view_manager.h"

class RoomManager {
 public:
  RoomManager(OptionManager* option_manager, ViewManager* view_manager,
              Player* player, EnemyManager* enemy_manager,
              ItemManager* item_manager, SaveManager* save_manager);
  void AddRoom(int id);
  Room* GetRoom(int id);
  bool RoomProcess(int id);

 private:
  LRUCache<Room> rooms_;
  OptionManager* option_manager_;
  ViewManager* view_manager_;
  Player* player_;
  EnemyManager* enemy_manager_;
  ItemManager* item_manager_;
  SaveManager* save_manager_;
};

#endif  // ROOM_MANAGER_H_
