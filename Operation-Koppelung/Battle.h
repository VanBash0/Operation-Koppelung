#ifndef BATTLE_H_
#define BATTLE_H_

#include <memory>
#include <string>
#include <vector>

#include "enemy_manager.h"
#include "player.h"
#include "view_manager.h"

class Battle {
 public:
  Battle(std::shared_ptr<Player> player,
         std::vector<std::shared_ptr<Enemy>> enemies,
         std::shared_ptr<ViewManager> view_manager);

  void PlayerTurn(const std::vector<std::shared_ptr<Attack>>& spells,
                  const std::vector<std::string>& spell_names);

 private:
  bool HandleAttack();
  bool HandleMagic(const std::vector<std::shared_ptr<Attack>>& spells,
                   const std::vector<std::string>& spell_names);
  void HandleDefend();
  bool HandleItem();
  void RemoveDeadEnemies();
  bool IsBattleOver() const;

  std::shared_ptr<Player> player_;
  std::vector<std::shared_ptr<Enemy>> enemies_;
  std::shared_ptr<ViewManager> view_manager_;

  int player_defence_ = 0;
};

#endif  // BATTLE_H_
