#ifndef GAME_H_
#define GAME_H_

#include "attack_manager.h"
#include "enemy_manager.h"
#include "item_manager.h"
#include "option_manager.h"
#include "player.h"
#include "room_manager.h"
#include "view_manager.h"

class Game {
 private:
  std::unique_ptr<AttackManager> attack_manager_;
  std::unique_ptr<OptionManager> option_manager_;
  std::unique_ptr<EnemyManager> enemy_manager_;
  std::unique_ptr<RoomManager> room_manager_;
  std::unique_ptr<ItemManager> item_manager_;
  std::unique_ptr<Player> player_;
  std::unique_ptr<ViewManager> view_manager_;

 public:
  Game();
  void Run();   // Основной цикл программы
  void Play();  // Непосредственно игра
};

#endif  // GAME_H_
