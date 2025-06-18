#ifndef OPTION_H_
#define OPTION_H_

#include <memory>
#include <string>
#include <vector>

#include "battle.h"
#include "item_manager.h"
#include "player.h"
#include "view_manager.h"

class Option {
 public:
  std::string GetDescription() const { return description_; }
  virtual void Execute(ViewManager* view_manager, Player* player,
                       ItemManager* item_manager,
                       EnemyManager* enemy_manager) = 0;
  virtual ~Option() = default;

 protected:
  Option(std::string description, std::string story, std::string after_story,
         bool is_picked)
      : description_(description),
        story_(story),
        after_story_(after_story),
        is_picked_(is_picked) {};

  std::string description_;
  std::string story_;        // Текст, выводящийся при первом выборе опции
  std::string after_story_;  // Текст, выводящийся при последующих выборах опции
  bool is_picked_;
};

class ExplorationOption : public Option {
 public:
  void Execute(ViewManager* view_manager, Player* player,
               ItemManager* item_manager, EnemyManager* enemy_manager) override;

  ExplorationOption(std::string description, std::string story,
                    std::string after_story, bool is_picked, int loot_id)
      : Option{description, story, after_story, is_picked},
        loot_id_(loot_id) {};

 private:
  int loot_id_;
};

class GramophoneOption : public Option {
 public:
  void Execute(ViewManager* view_manager, Player* player,
               ItemManager* item_manager, EnemyManager* enemy_manager) override;

  GramophoneOption(std::string description, std::string story,
                   std::string after_story, bool is_picked, int sanity_restore)
      : Option{description, story, after_story, is_picked},
        sanity_restore_(sanity_restore) {};

 private:
  int sanity_restore_;
};

class BattleOption : public Option {
 public:
  void Execute(ViewManager* view_manager, Player* player,
               ItemManager* item_manager, EnemyManager* enemy_manager) override;

  BattleOption(std::string description, std::string story,
               std::string after_story, bool is_picked,
               const std::vector<int>& enemies_id)
      : Option{description, story, after_story, is_picked},
        enemies_id_(enemies_id) {};

 private:
  std::vector<int> enemies_id_;
};

class RoomChangeOption : public Option {
 public:
  void Execute(ViewManager* view_manager, Player* player,
               ItemManager* item_manager, EnemyManager* enemy_manager) override;

  RoomChangeOption(std::string description, std::string story,
                   std::string after_story, bool is_picked, int room_id)
      : Option{description, story, after_story, is_picked},
        room_id_(room_id) {};

 private:
  int room_id_;
};

#endif  // OPTION_H_
