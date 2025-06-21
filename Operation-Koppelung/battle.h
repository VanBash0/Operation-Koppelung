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
  Battle(const std::vector<int>& enemies_id, EnemyManager* enemy_manager,
         Player* player, ViewManager* view_manager);
  bool ExecuteBattle();

 private:
  void PlayerTurn(const std::vector<Attack*>& spells,
                  const std::vector<std::string>& spell_names);

  void EnemiesTurn();
  bool HandleAttack();
  bool HandleMagic(const std::vector<Attack*>& spells,
                   const std::vector<std::string>& spell_names);
  void HandleDefend();
  bool HandleItem();
  void RemoveDeadEnemies();
  bool IsBattleOver() const;

  Player* player_;
  ViewManager* view_manager_;
  std::vector<std::unique_ptr<Enemy>> enemies_;

  int player_defence_ = 0;
};

#endif  // BATTLE_H_
